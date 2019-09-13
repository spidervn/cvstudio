#include "CPoultryMonitorApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

enum PoultryBehavior
{
    WingSpreading,
    Bristling,
    Drinking,
    Scratching,
    Resting,
    Stretching,
    Preening,
    Mounting,
    Inactivity
};

class CIdentityBroilerBehavior
{
public:
    static void calculateShapeCoeff(double area, double perimeter, double dmin, double dmax,
                                    double& cc,
                                    double& cc_max,
                                    double& cc_min)
    {
        cc = perimeter * perimeter / ( 4 * CV_PI * area);
        cc_max = CV_PI * dmax * dmax / area;
        cc_min = CV_PI * dmin * dmin / area;
    }

    static void calculateShapeCoeff(
            int nFrames,
            vector<double> vArea,
            vector<double> vPerimeter,
            vector<double> vDmin,
            vector<double> vDmax,
            vector<double> vCC,
            vector<double> vCCMax,
            vector<double> vCCMin)
    {
        double A_ave;
        double P_ave;
        double Dmax_ave;
        double Dmin_ave;
        double CC_ave;
        double CC_max_ave;
        double CC_min_ave;
        double A_sd;    // Standard deviation of area A
        double P_sd;    // Standard deviation of area P
        double D_max_sd;
        double D_min_sd;
        double CC_sd;
        double CC_max_sd;
        double CC_min_sd;
        double VA;  // Area gain velocity
        double VP;  // Perimeter gain velocity
        double VDmax;   // Maximum distance increase velocity
        double VDmin;   // Minimum distance increase velocity
        double VCC;     // Coefficient of shape convergence velocity
        double VCC_max; // Maximum coefficient of shape convergence velocity
        double VCC_min;
        double ratio;   // Dmin/Dmax

        A_ave = std::accumulate(vArea.begin(), vArea.begin() + nFrames, (double)0)/ nFrames;
        P_ave = std::accumulate(vPerimeter.begin(), vPerimeter.begin() + nFrames, (double)0)/nFrames;
        Dmax_ave = std::accumulate(vDmax.begin(), vDmax.begin() + nFrames, (double)0)/nFrames;
        Dmin_ave = std::accumulate(vDmin.begin(), vDmin.begin() + nFrames, (double)0)/nFrames;
        CC_ave = std::accumulate(vCC.begin(), vCC.begin() + nFrames, (double)0)/nFrames;
        CC_max_ave = std::accumulate(vCCMax.begin(), vCCMax.begin() + nFrames, (double)0) / nFrames;
        CC_min_ave = std::accumulate(vCCMin.begin(), vCCMin.begin() + nFrames, (double)0) / nFrames;
        

        // variance = sum (x[i]* P(x[i]) / ;
        // variance = E((x-mi)^2)
        // variance = E((x-mi)^2)
        // variance = sum{i} p(i) * (x-mi)^2

        auto f_varianceArea = [=](double a, double b) {
            return a + (b - A_ave) * (b - A_ave);
        };
        auto f_variancePeri = [=](double a, double b) {
            return a + (b - P_ave) * (b - P_ave);
        };
        auto f_varianceDmax = [=](double a, double b) {
            return a + (b - Dmax_ave)*(b - Dmax_ave);
        };
        auto f_varianceDmin = [=](double a, double b) {
            return a + (b - D_min_sd)*(b - D_min_sd);
        };
        auto f_varianceCC = [=](double a, double b) {
            return a + (b - CC_ave)*(b - CC_ave);
        };
        auto f_varianceCCMax = [=](double a, double b) {
            return a + (b - CC_max_ave)*(b - CC_max_ave);
        };
        auto f_varianceCCMin = [=](double a, double b) {
            return a + (b - CC_min_ave)*(b - CC_min_ave);
        };

        double variance_A = std::accumulate(vArea.begin(), vArea.begin() + nFrames, (double)0, f_varianceArea) / nFrames;
        double variance_P = std::accumulate(vPerimeter.begin(), vPerimeter.begin() + nFrames, (double)0, f_variancePeri) / nFrames;
        double variance_Dmax = std::accumulate(vDmax.begin(), vDmax.begin() + nFrames, (double)0, f_varianceDmax) / nFrames;
        double variance_Dmin = std::accumulate(vDmin.begin(), vDmin.begin() + nFrames, (double)0, f_varianceDmin) / nFrames;
        double variance_CC = std::accumulate(vCC.begin(), vCC.begin() + nFrames, (double)0, f_varianceCC) / nFrames;
        double variance_CCMax = std::accumulate(vCCMax.begin(), vCCMax.begin() + nFrames, (double)0, f_varianceCCMax) / nFrames;
        double variance_CCMin = std::accumulate(vCCMin.begin(), vCCMin.begin() + nFrames, (double)0, f_varianceCCMin) / nFrames;
        
        A_sd = sqrt(variance_A);
        P_sd = sqrt(variance_P);
        D_max_sd = sqrt(variance_Dmax);
        D_max_sd = sqrt(variance_Dmax);
        D_min_sd = sqrt(variance_Dmin);
        CC_sd = sqrt(variance_CC);
        CC_max_sd = sqrt(variance_CCMax);
        CC_min_sd = sqrt(variance_CCMin);

        VA = (vArea[nFrames-1] - vArea[0])/ nFrames;
        VP = (vPerimeter[nFrames-1] - vPerimeter[0]) / nFrames;
        VDmax = (vDmax[nFrames - 1] - vDmax[0]) / nFrames;
        VDmin = (vDmin[nFrames - 1] - vDmin[0]) / nFrames;
        VCC = (vCC[nFrames - 1] - vCC[0]) / nFrames;
        VCC_max = (vCCMax[nFrames - 1] - vCCMax[0]) / nFrames;
        VCC_min = (vCCMin[nFrames - 1] - vCCMin[0]) / nFrames;
        // ratio = ?    
    }
    
    static PoultryBehavior classify()
    {
        double A_ave;
        double P_ave;
        double Dmax_ave;
        double Dmin_ave;
        double CC_ave;
        double CC_max_ave;
        double CC_min_ave;
        double A_sd;    // Standard deviation of area A
        double P_sd;    // Standard deviation of area P
        double D_max_sd;
        double D_min_sd;
        double CC_sd;
        double CC_max_sd;
        double CC_min_sd;
        double VA;  // Area gain velocity
        double VP;  // Perimeter gain velocity
        double VDmax;   // Maximum distance increase velocity
        double VDmin;   // Minimum distance increase velocity
        double VCC;     // Coefficient of shape convergence velocity
        double VCC_max; // Maximum coefficient of shape convergence velocity
        double VCC_min;
        double ratio;   // Dmin/Dmax

        PoultryBehavior ret;

        if (VP > 13.5)
        {
            return WingSpreading;
        }
        else if (P_ave <= 139.25)
        {
            return Inactivity;
        }
        else 
        {
            if (A_sd > 52.55)
            {
                if (P_ave > 243.25)
                {
                    return Mounting;
                }
                else 
                {
                    if (A_ave > 1049)
                    {
                        if (A_sd > 114.71)
                        {
                            if (CC_min_ave > 2.52)
                            {
                                if (D_max_sd > 0.92)
                                {
                                    return Bristling;
                                }
                                else
                                {
                                    return Stretching;
                                }
                            }
                            else
                            {
                                if (CC_ave > 2.33)
                                {
                                    if (VA > 69.25)
                                    {
                                        return Stretching;
                                    }
                                    else
                                    {
                                        return Bristling;
                                    }
                                }
                                else
                                {
                                    return Stretching;
                                }
                            }
                        }
                        else
                        {
                            if (D_min_sd > 1.73)
                            {
                                return Stretching;
                            }
                            else
                            {
                                if (ratio > 0.38)
                                {
                                    if (VDmin > 0.57)
                                    {
                                        return Bristling;
                                    }
                                    else
                                    {
                                        return Preening;
                                    }
                                }
                                else
                                {
                                    return Stretching;
                                }
                            }
                            
                        }
                    }
                    else
                    {
                        if (VA > -0.8)
                        {
                            return Bristling;
                        }
                        else
                        {
                            return Scratching;
                        }
                        
                    }
                    
                }
            }
            else
            {
                if (CC_max_ave > 2.49)
                {
                    if (CC_max_sd > 0.96)
                    {
                        if (P_ave > 168.75)
                        {
                            return Resting;
                        }
                        else
                        {
                            return Inactivity;
                        }
                        
                    }
                    else
                    {
                        if(VDmin > -0.06)
                        {
                            return Drinking;
                        }
                        else
                        {
                            if (VCC_min > -0.06)
                            {
                                return Scratching;
                            }
                            else
                            {
                                return Drinking;
                            }
                        }
                    }                    
                }
                else
                {
                    if (D_max_sd > 1.01)
                    {
                        if (CC_min_sd > 0.46)
                        {
                            return Preening;
                        }
                        else
                        {
                            return Scratching;
                        }
                    }
                    else
                    {
                        if (VDmax > 0.275)
                        {
                            return Drinking;
                        }
                        else
                        {
                            if (D_min_sd > 0.31)
                            {
                                if (VDmax > -0.12)
                                {
                                    if (Dmin_ave > 9.5)
                                    {
                                        return Resting;
                                    }
                                    else
                                    {
                                        return Preening;
                                    }
                                    
                                }
                                else
                                {
                                    return Preening;
                                }                                
                            }
                            else
                            {
                                if (VDmin > 0.05)
                                {
                                    return Scratching;
                                }
                                else
                                {
                                    return Resting;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};

CPoultryMonitorApp::CPoultryMonitorApp()
{}

CPoultryMonitorApp::~CPoultryMonitorApp()
{}

int CPoultryMonitorApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    // return run_paper(argv[1]);
    // return run_watershed(argv[1]);
    return run_extract(argv[1]);
    return run_video(argv[1]);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int morph_size = 1;
    Mat img = imread(argv[1]);
    Mat imgGray;
    Mat dst;
    Mat dstOpen;
    Mat element = getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );    

    cvtColor(img,imgGray, COLOR_BGR2GRAY);
    threshold(imgGray, dst, 155, 255, THRESH_BINARY);

    morphologyEx(dst, dstOpen, cv::MORPH_OPEN, element);

    // Thresholding
    const char* szImgGray = "Gray";
    const char* szThreshold = "Threshold";
    const char* szOpening = "Openning";

    namedWindow(szImgGray, WINDOW_AUTOSIZE);
    namedWindow(szThreshold, WINDOW_AUTOSIZE);
    namedWindow(szOpening, WINDOW_AUTOSIZE);

    imshow(szImgGray, imgGray);
    imshow(szThreshold, dst);
    imshow(szOpening, dstOpen);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[µs]" << std::endl;

    // Reading a video 
    /*
    {
        // Reading a video
        VideoCapture capRefFrnc(argv[1]);
        
        if (!capRefFrnc.isOpened())
        {
            printf("Could not open\r\n");
            return -1;
        }

        Size refS = Size((int) capRefFrnc.get(CAP_PROP_FRAME_WIDTH), 
                            (int) capRefFrnc.get(CAP_PROP_FRAME_HEIGHT));
        Mat frame;

        for (int i=0; i<10;++i)
        {
            capRefFrnc >> frame ;
            String str = "frame_";
            str += i;
            str += ".jpg";

            imwrite(str, frame);
        }
    }
    */

    waitKey();
    return 0;
}

int CPoultryMonitorApp::run_watershed(const char* szFile)
{
    // Mat src = 
    Mat src = imread(szFile, IMREAD_COLOR);

    const char* sz01 = "Source";
    const char* sz02 = "Source black";

    //namedWindow(sz01, WINDOW_AUTOSIZE);
    //namedWindow(sz02, WINDOW_AUTOSIZE);
    imshow(sz01, src);

    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3,3) <<
                                1,  1, 1,
                                1, -8, 1,
                                1,  1, 1); // an approximation of second derivative, a quite strong kernel
    Mat imgLaplacian;
    Mat sharp;
    Mat imgResult;
    Mat bw;
    
    for (int y=0; y < src.rows; ++y)
    {
        for (int x=0; x < src.cols; ++x)
        {
            if (src.at<Vec3b>(y,x) == Vec3b(255, 255, 255))
            {
                src.at<Vec3b>(y, x)[0] = 0;
                src.at<Vec3b>(y, x)[1] = 0;
                src.at<Vec3b>(y, x)[2] = 0;
            }
        }
    }

    imshow(sz02, src);
    filter2D(src, imgLaplacian, CV_32F, kernel);

    src.convertTo(sharp, CV_32F);
    imgResult = sharp - imgLaplacian;

    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    // Create binary image
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);        
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    
    // Perform DF.
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);

    imshow("Sharp", sharp);
    imshow("Laplace", imgLaplacian);
    imshow("Result", imgResult);
    imshow("BinaryImg", bw);
    imshow("Distance transform", dist);

    // Threshold
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);
    
    // Dilate a bit the dist image 
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);

    // Crate the CV_8U version 
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find total markers
    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Create the marker 
    Mat markers = Mat::zeros(dist.size(), CV_32S);
    for (int i=0; i< contours.size(); ++i)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);
    }

    // Draw the background marker 
    circle(markers, Point(5,5), 3, Scalar(255), -1);
    imshow("Markers", markers * 1000);

    // Perform the watershed algorithm
    watershed(imgResult, markers);
    Mat mark;

    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);

    vector<Vec3b> colors;
    for (size_t i=0; i<contours.size(); ++i)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);

        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // Craete the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int>(contours.size()))
            {
                dst.at<Vec3b>(i,j) = colors[index-1];
            }
        }
    }
    // Visualize the final image
    imshow("Final Result", dst);
    

    waitKey();
    return 0;
}

int CPoultryMonitorApp::run_paper(const char* szFile)
{
    Mat img;
    Mat imgHSL;
    img = imread(szFile, IMREAD_COLOR);
    cvtColor(img, imgHSL, COLOR_BGR2HLS_FULL);

    // Image processing 
    int count = 0;

    Mat_<Vec3d> I_ = imgHSL;
    printf("Before Normalize:\r\n");
    for (int y=0; y<imgHSL.rows; ++y)
    {
        for (int x=0; x<imgHSL.cols; ++x)
        {
            printf("\t(%d,%d)=%f,%f,%f\r\n", y, x, I_(y,x)[0], I_(y,x)[1], I_(y,x)[2]);

            if (count ++ > 20)    
            {
                break;
            }
        }
        if (count ++ > 20)    
        {
            break;
        }
    }

    normalize(imgHSL, imgHSL, 0, 1.0, NORM_MINMAX);
    
    count = 0;
    I_ = imgHSL;
    printf("after Normalize:\r\n");
    for (int y=0; y<imgHSL.rows; ++y)
    {
        for (int x=0; x<imgHSL.cols; ++x)
        {
            printf("\t(%d,%d)=%f,%f,%f\r\n", y, x, I_(y,x)[0], I_(y,x)[1], I_(y,x)[2]);

            if (count ++ > 20)    
            {
                break;
            }
        }
        if (count ++ > 20)    
        {
            break;
        }
    }
    // Image analysis

    return 0;
}

int CPoultryMonitorApp::run_video(const char* szFile)
{
    cv::Mat img;
    printf("A\r\n");

    VideoCapture video(szFile);
    printf("A1\r\n");

    if (!video.isOpened())
    {
        printf("Video could not opened\r\n");
        return -1;
    }

    printf("Width=%d,Height=%d,FPS=%d\r\n", 
                    (int) video.get(CAP_PROP_FRAME_WIDTH), 
                    (int) video.get(CAP_PROP_FRAME_HEIGHT),
                    (int) video.get(CAP_PROP_FRAME_COUNT));
    Mat frame;
    vector<int> compression_params;
    compression_params.push_back( CV_IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 100 );

    // video.set(CV_CAP_PROP_POS_FRAMES, 11000-1);
    video.set(CV_CAP_PROP_POS_FRAMES, 11090-1);

    for (int i=0; i < 25; ++i)
    {
        video >> frame;
        char tmp[255];

        sprintf(tmp, "frame_%d.jpg", i);
        cv::String file = tmp;
        printf("%s\r\n", file.c_str());

        imwrite(file, frame, compression_params);
    }

    return 0;
}

int CPoultryMonitorApp::run_extract(const char* szFile)
{
    Mat img = imread(szFile, IMREAD_COLOR);
    Mat imgGray;
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    imshow("Gray", imgGray);

    waitKey();
    return 0;
}