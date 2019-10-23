#include "CPoultryMonitorApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include "app/impl/general/CFileUtil.h"
#include "app/impl/cv/CCVCore.h"
#include "inih-master/INIReader.h"
#include <sys/stat.h>
using namespace cv;
using namespace std;

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

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
    static string str(PoultryBehavior b)
    {
        PoultryBehavior arrB[] = {
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

        string names[] = {
            "WingSpreading",
            "Bristling",
            "Drinking",
            "Scratching",
            "Resting",
            "Stretching",
            "Preening",
            "Mounting",
            "Inactivity"
        };

        int n = ARRAYSIZE(arrB);

        for (int i=0; i<n; ++i)
        {
            if (arrB[i] == b)
            {
                return names[i];
            }
        }

        return "";
    }

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
                        vector<double>& vCc,
                        vector<double>& vCc_max,
                        vector<double>& vCc_min)
    {
        for (int i=0; i<nFrames; ++i)
        {
            vCc[i] = vPerimeter[i] * vPerimeter[i]/(4 * CV_PI * vArea[i]);
            vCc_max[i] = CV_PI * vDmax[i] * vDmax[i] / vArea[i];
            vCc_min[i] = CV_PI * vDmin[i] * vDmin[i] / vArea[i];
        }
    }

    static void calculateShapeCoeff(
            int nFrames,
            vector<double> vArea,
            vector<double> vPerimeter,
            vector<double> vDmin,
            vector<double> vDmax,
            vector<double>& vCC,
            vector<double>& vCCMax,
            vector<double>& vCCMin,
            double& A_ave,
            double& P_ave,
            double& Dmax_ave,
            double& Dmin_ave,
            double& CC_ave,
            double& CC_max_ave,
            double& CC_min_ave,
            double& A_sd,    // Standard deviation of area A
            double& P_sd,    // Standard deviation of area P
            double& D_max_sd,
            double& D_min_sd,
            double& CC_sd,
            double& CC_max_sd,
            double& CC_min_sd,
            double& VA,  // Area gain velocity
            double& VP,  // Perimeter gain velocity
            double& VDmax,   // Maximum distance increase velocity
            double& VDmin,   // Minimum distance increase velocity
            double& VCC,     // Coefficient of shape convergence velocity
            double& VCC_max, // Maximum coefficient of shape convergence velocity
            double& VCC_min,
            double& ratio)   // Dmin/Dmax)
    {
        printf("Done %d; %d; %d; \r\n", vArea.size());

        for (int i=0; i<nFrames; ++i)
        {
            vCC.push_back( vPerimeter[i] * vPerimeter[i]/(4 * CV_PI * vArea[i]));
            vCCMax.push_back(CV_PI * vDmax[i] * vDmax[i] / vArea[i]);
            vCCMin.push_back(CV_PI * vDmin[i] * vDmin[i] / vArea[i]);
        }

        printf("Done %d\r\n", vArea.size());

        A_ave = std::accumulate(vArea.begin(), vArea.begin() + nFrames, (double)0)/ nFrames;
        printf("Done1\r\n");
        P_ave = std::accumulate(vPerimeter.begin(), vPerimeter.begin() + nFrames, (double)0)/nFrames;
        Dmax_ave = std::accumulate(vDmax.begin(), vDmax.begin() + nFrames, (double)0)/nFrames;
        Dmin_ave = std::accumulate(vDmin.begin(), vDmin.begin() + nFrames, (double)0)/nFrames;
        CC_ave = std::accumulate(vCC.begin(), vCC.begin() + nFrames, (double)0)/nFrames;
        CC_max_ave = std::accumulate(vCCMax.begin(), vCCMax.begin() + nFrames, (double)0) / nFrames;
        CC_min_ave = std::accumulate(vCCMin.begin(), vCCMin.begin() + nFrames, (double)0) / nFrames;
        printf("Done1\r\n");

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
        
        ratio = std::accumulate(vDmin.begin(), vDmin.begin() + nFrames, (double)0) / std::accumulate(vDmax.begin(), vDmax.begin() + nFrames, (double)0);
    }
    
    static PoultryBehavior classify(int nFrames,
            vector<double> vArea,
            vector<double> vPerimeter,
            vector<double> vDmin,
            vector<double> vDmax,
            vector<double> vCC,
            vector<double> vCCMax,
            vector<double> vCCMin,
            double A_ave,
            double P_ave,
            double Dmax_ave,
            double Dmin_ave,
            double CC_ave,
            double CC_max_ave,
            double CC_min_ave,
            double A_sd,    // Standard deviation of area A
            double P_sd,    // Standard deviation of area P
            double D_max_sd,
            double D_min_sd,
            double CC_sd,
            double CC_max_sd,
            double CC_min_sd,
            double VA,  // Area gain velocity
            double VP,  // Perimeter gain velocity
            double VDmax,   // Maximum distance increase velocity
            double VDmin,   // Minimum distance increase velocity
            double VCC,     // Coefficient of shape convergence velocity
            double VCC_max, // Maximum coefficient of shape convergence velocity
            double VCC_min,
            double ratio)
    {
        /*
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
        */

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

    static int readInput(const char* szFile,
                                    vector<double>& vArea,
                                    vector<double>& vPeri,
                                    vector<double>& vDmin,
                                    vector<double>& vDmax)
    {
        ifstream file(szFile);
        double d1;
        double d2;
        double d3;
        double d4;

        printf("Start read file:\r\n");
        while (file.good())
        {
            file >> d1;
            file >> d2;
            file >> d3;
            file >> d4;

            // printf("\t%f\r\n", d1);
            vArea.push_back(d1);
            vPeri.push_back(d2);
            vDmin.push_back(d3);
            vDmax.push_back(d4);
        }

        printf("Finish\r\n");

        file.close();
    }

    static int run(const char* szFile, PoultryBehavior& behav)
    { 
        int nFrames;
        vector<double> vArea;
        vector<double> vPerimeter;
        vector<double> vDmin;
        vector<double> vDmax;
        vector<double> vCC;
        vector<double> vCCMax;
        vector<double> vCCMin;
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
        double ratio;
        PoultryBehavior behavior;

        readInput(szFile, vArea, vPerimeter, vDmin, vDmax);
        nFrames = vArea.size();
        printf("size=%d\r\n", vArea.size());
        calculateShapeCoeff(nFrames, 
                        vArea,
                        vPerimeter,
                        vDmin,
                        vDmax,
                        vCC,
                        vCCMax,
                        vCCMin,
                        A_ave,
                        P_ave,
                        Dmax_ave,
                        Dmin_ave,
                        CC_ave,
                        CC_max_ave,
                        CC_min_ave,
                        A_sd,    // Standard deviation of area A
                        P_sd,    // Standard deviation of area P
                        D_max_sd,
                        D_min_sd,
                        CC_sd,
                        CC_max_sd,
                        CC_min_sd,
                        VA,  // Area gain velocity
                        VP,  // Perimeter gain velocity
                        VDmax,   // Maximum distance increase velocity
                        VDmin,   // Minimum distance increase velocity
                        VCC,     // Coefficient of shape convergence velocity
                        VCC_max, // Maximum coefficient of shape convergence velocity
                        VCC_min,
                        ratio);

        behavior = classify(nFrames, 
                        vArea,
                        vPerimeter,
                        vDmin,
                        vDmax,
                        vCC,
                        vCCMax,
                        vCCMin,
                        A_ave,
                        P_ave,
                        Dmax_ave,
                        Dmin_ave,
                        CC_ave,
                        CC_max_ave,
                        CC_min_ave,
                        A_sd,    // Standard deviation of area A
                        P_sd,    // Standard deviation of area P
                        D_max_sd,
                        D_min_sd,
                        CC_sd,
                        CC_max_sd,
                        CC_min_sd,
                        VA,  // Area gain velocity
                        VP,  // Perimeter gain velocity
                        VDmax,   // Maximum distance increase velocity
                        VDmin,   // Minimum distance increase velocity
                        VCC,     // Coefficient of shape convergence velocity
                        VCC_max, // Maximum coefficient of shape convergence velocity
                        VCC_min,
                        ratio);

        printf("Behavior detected = %s\r\n", str(behavior).c_str());
        return 0;
    }

    static int getRectOfBroiler(Mat frame, vector<Rect>& v)
    {
        v.clear();

        /*
         * 1- Find every connected components 
         * 2- Then choose rects whose similar to Square (ratio~ 3/4 -> 4.3) and ( threshold_low <= area < threshold_hig)
         */
        int area_low = 70*70; //450;
        int area_hig = 90*90; //1325;
        int threshval = 150;
        Mat bw = threshval < 128 ? (frame < threshval) : (frame > threshval);
    
        Mat labelImage(frame.size(), CV_32S);
        int nLabels = connectedComponents(bw, labelImage, 8);
        std::vector<Vec3b> colors(nLabels);
        std::vector<Rect> rect(nLabels);

        colors[0] = Vec3b(0, 0, 0);//background
        rect[0] = cv::Rect(-1,-1,-1,-1);
        for(int label = 1; label < nLabels; ++label){
            colors[label] = Vec3b( (rand()&255), (rand()&255), (rand()&255) );
            rect[label] = cv::Rect(-1,-1,-1,-1);
        }

        Mat dst(frame.size(), CV_8UC3);
        for(int r = 0; r < dst.rows; ++r) {
            for(int c = 0; c < dst.cols; ++c) {
                int label = labelImage.at<int>(r, c);
                Vec3b &pixel = dst.at<Vec3b>(r, c);
                pixel = colors[label];

                //
                // Trick: use width & height to store (right, bottom)
                //
                if (rect[label].x == -1)
                {
                    rect[label].x = c;
                }
                else if (c < rect[label].x)
                {
                    rect[label].x = c;
                }
                if (rect[label].width == -1)
                {
                    rect[label].width = c;
                }
                else if (rect[label].width < c)
                {
                    rect[label].width = c;
                }            

                if (rect[label].y == -1)
                {
                    rect[label].y = r;
                }
                else if (r < rect[label].y)
                {
                    rect[label].y = r;
                }

                if (rect[label].height == -1)
                {
                    rect[label].height = r;                
                }
                else if ( rect[label].height < r)
                {
                    rect[label].height = r;
                }
            }
        }

        for (int label=1; label < nLabels; ++label)
        {
            // Un-trick
            rect[label].width = rect[label].width - rect[label].x;
            rect[label].height = rect[label].height - rect[label].y;

            if (rect[label].width > 0)
            {
                double ratio = (double)rect[label].height / (double)rect[label].width;
                int area = rect[label].width * rect[label].width;

                if (ratio >= 0.35 && ratio <= 1.9 && area >= area_low && area <= area_hig)
                {
                    // cv::rectangle(dst, v[label], );
                    v.push_back(rect[label]);
                }
            }
        }

        // imshow("ConnectedComponents", dst);

        return 0;
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

    // 
    // return run_paper(argv[1]);
    // return run_watershed(argv[1]);
    //
    //return run_contours(argv[1], atoi(argv[2]));
    return run_video_seg(argv[1], argv[2]);
    return run_morph(argv[1]);
    return examine_watershed(argv[1], argv[2]);
    return run_segmentation2(argv[1], argv[2]);
    return run_video(argv[1], argv[2]);
    return run_video(argv[1], argv[2]);
    PoultryBehavior bh;
    //return CIdentityBroilerBehavior::run(argv[1], bh);
    //return run_contours(argv[1], atoi(argv[2]));
    //return run_morph(argv[1]);
    return run_watershed(argv[1]);
    return run_extract(argv[1]);
    return run_video(argv[1], argv[2]);
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
    imshow("Markers", markers * 10000);

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

int CPoultryMonitorApp::run_video(const char* szFile, const char* szIni)
{
    cv::Mat img;
    printf("A\r\n");
    INIReader ini(szIni);

    if (ini.ParseError() != 0)
    {
        printf("Read failed\r\n");
        return 0;
    }

    int low_h;
    int low_s;
    int low_v;
    int hig_h;
    int hig_s;
    int hig_v;
    int video_w;
    int video_h;

    low_h = ini.GetInteger("hsv", "low_h", -1);
    low_s = ini.GetInteger("hsv", "low_s", -1);
    low_v = ini.GetInteger("hsv", "low_v", -1);
    hig_h = ini.GetInteger("hsv", "hig_h", -1);
    hig_s = ini.GetInteger("hsv", "hig_s", -1);
    hig_v = ini.GetInteger("hsv", "hig_v", -1);

    VideoCapture video(szFile);
    printf("A1\r\n");
    video_w = video.get(CAP_PROP_FRAME_WIDTH);
    video_h = video.get(CAP_PROP_FRAME_HEIGHT);

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
    Mat frameHSV;
    Mat frameIR;
    VideoWriter videoOut;
    int ex = static_cast<int>(video.get(CAP_PROP_FOURCC)); 
    vector<int> compression_params;
    compression_params.push_back( CV_IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 100 );

    // video.set(CV_CAP_PROP_POS_FRAMES, 11000-1);
    // video.set(CV_CAP_PROP_POS_FRAMES, 11090-1);
    namedWindow("Video", WINDOW_AUTOSIZE);
    namedWindow("IR", WINDOW_AUTOSIZE);
    namedWindow("Video-chick", WINDOW_AUTOSIZE);
    namedWindow("ConnectedComponents");

    ICVCorePtr ccp = CCVCorePtrNew;
    int index=0;
    vector<Mat> vBlock;
    vector<Rect> vRect;

    videoOut.open("background_subtract.avi", 
                    ex, 
                    video.get(CAP_PROP_FPS),
                    Size(video_w, video_h),
                    true);
    int frameIdx = 0;   // Frame index
    for (;;)
    {
        char szFolder[255];
        frameIdx++;
        sprintf(szFolder, "store/frames%d", frameIdx);
        mkdir(szFolder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        Mat frameBuck;
        Mat frameFilter;
        Mat frameChicken;
        Mat frameChickenGray;
        video >> frame;
        if (frame.empty())
        {
            if (vBlock.size() > 0)
            {
                // Process a block of 30 frames here
            }

            break;
        }

        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        char tmp[255];
        char tmp2[255];
        char tmp3[255];

        inRange(frameHSV, Scalar(low_h, low_s, low_v), Scalar(hig_h, hig_s, hig_v), frameIR);

        /*
        Mat_<Vec3b> _I = frameHSV;

        for (int y=0; y<frameHSV.rows; ++y)
        {
            for (int x=0; x<frameHSV.cols; ++x)
            {
                _I(y,x)[2] = 150;
                // _I(y,x)[2] = 100;
            }
        }
        */

        rectangle(frameIR, cv::Rect(100, 100, 300, 250), Scalar(0,255,255), 2);

        ccp->bucketingColor(frame, 50, frameBuck);
        inRange(frameBuck, Scalar(140,140,140), Scalar(210,210,210), frameFilter);

        frame.copyTo(frameChicken, frameFilter);
        cvtColor(frameChicken, frameChickenGray, COLOR_BGR2GRAY);

        // sprintf(tmp, "frame_%d.jpg", i);
        // cv::String file = tmp;
        // printf("%s\r\n", file.c_str());

        CIdentityBroilerBehavior::getRectOfBroiler(frameChickenGray, vRect);
        char szFile[255];

        for (int i=0; i<vRect.size(); ++i)
        {
            rectangle(frameHSV, vRect[i], Scalar(0,255,255));

            Mat imgChick = frame(vRect[i]);
            sprintf(szFile, "store/frames%d/chick_%d.png", frameIdx, i);
            printf("File Save=%s\r\n", szFile);
            imwrite(szFile, imgChick);
        }

        // imwrite(file, frame, compression_params);
        imshow("IR", frameIR);
        imshow("Video", frameHSV);
        imshow("Video-chick", frameChicken);

        char c = (char)waitKey(25);
        if (c == 27) break;

        if (index++ < 25)
        {
            sprintf(tmp, "frame_%d.png", index);
            sprintf(tmp2, "frame_hsv_%d.png", index);
            sprintf(tmp3, "frame_bgsub_%d.png", index);

            imwrite(tmp, frame, compression_params);
            imwrite(tmp2, frameHSV, compression_params);
            imwrite(tmp3, frameChicken, compression_params);
        }

        if (vBlock.size() == 30)
        {
            // Process a block of 30 frames here
        }

        videoOut << frameChicken;
    }

    printf("Finish");
    waitKey();
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

int CPoultryMonitorApp::run_contours(const char* szFile, int thresh)
{
    RNG rng(12345);
    Mat src = imread(szFile);
    Mat src_gray;
    Mat canny_out;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3,3));

    Canny(src_gray, canny_out, thresh, thresh * 2);
    findContours(canny_out, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }

    imshow("Source", src);
    imshow("Contours", drawing);

    waitKey();
    return 0;
}

int CPoultryMonitorApp::run_morph(const char* szFile)
{
    Mat src = imread(szFile, IMREAD_COLOR);
    Mat src_gray;
    Mat dst;
    Mat src_bucket;
    Mat dst_Rng;
    Mat dst_Filter;
    Mat dst_FilterMorph;
    Mat dst_Subtract;
    Mat elem;

    elem = getStructuringElement(MORPH_RECT, Size(3,3));
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    morphologyEx(src, dst, MORPH_GRADIENT, elem);

    inRange(src, Scalar(190, 190, 190), Scalar(255,255,255), dst_Rng);

    imshow("src", src);
    imshow("gradient", dst);
    imshow("thresholding", dst_Rng);

    imwrite("threshold.png", dst_Rng);

    ICVCorePtr ccp = CCVCorePtrNew;

    ccp->bucketingColor(src, 50, dst_Rng);
    imshow("Bucket", dst_Rng);
    imwrite("bucket.png", dst_Rng);
    // imwrite("gradient.png", dst);
    // 140; 140; 140    // Xa'm
    // 210; 210; 140    // vang nhat
    // 210; 210; 210;   // Trang
    // 210; 140; 140;   // Hong nhat

    inRange(dst_Rng, Scalar(140,140,140), Scalar(210,210,210), dst_Filter);
    imshow("Filter-before Morph", dst_Filter);  
    int morph_size = 1;
    morphologyEx(dst_Filter, dst_FilterMorph, MORPH_OPEN,
                        getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size )));
    morphologyEx(dst_FilterMorph, dst_FilterMorph, MORPH_CLOSE,
                        getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size )));

    imshow("Filter", dst_FilterMorph);  

    //cv::bitwise_and(src_gray, dst_Filter, dst_Subtract);
    src.copyTo(dst_Subtract, dst_Filter);    
    imshow("Background-sub", dst_Subtract);

    // 
    // Higher contrast
    // 
    

    waitKey();
    return 0;
}

int CPoultryMonitorApp::run_segmentation2(const char* szFile, const char* szIni)
{
    Mat img = imread(szFile, IMREAD_COLOR);
    Mat imgHSV;
    Mat imgIR;
    
    INIReader ini(szIni);

    if (ini.ParseError() != 0)
    {
        printf("Read failed\r\n");
        return 0;
    }

    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    int low_h;
    int low_s;
    int low_v;
    int hig_h;
    int hig_s;
    int hig_v;

    low_h = ini.GetInteger("hsv", "low_h", -1);
    low_s = ini.GetInteger("hsv", "low_s", -1);
    low_v = ini.GetInteger("hsv", "low_v", -1);
    hig_h = ini.GetInteger("hsv", "hig_h", -1);
    hig_s = ini.GetInteger("hsv", "hig_s", -1);
    hig_v = ini.GetInteger("hsv", "hig_v", -1);

    printf("InRange(%d,%d,%d)(%d,%d,%d)\r\n", low_h, low_s, low_v, hig_h, hig_s, hig_v);
    inRange(imgHSV, Scalar(low_h, low_s, low_v), 
                        Scalar(hig_h, hig_s, hig_v), 
                        imgIR);

    imshow("src", img);
    imshow("hsv", imgHSV);
    imshow("inrange", imgIR);

    waitKey();
    return 0;
}

int CPoultryMonitorApp::examine_watershed(const char* szFile, const char* szIni)
{
    // Extracting the extrema of a function f.
    double k_mf;
    double k_Mf;

    double f;
    double R_Xig_Xif;

    Mat img;
    Mat img_subtr_1;
    Mat imgXi;
    Mat imgXi_1;
    Mat imgZi;
    Mat imgRf_f_1;  // R_f(f-1) = R_X[i](f)(X[i](f-1)) = { x in X[i](f); E y in X[i](f-1); d_X[i](f)(x,y) finite}
    Mat labels;
    img = imread(szFile, IMREAD_GRAYSCALE);

    // 
    // k_m(f)(x) = 1    <=> x in m(f)
    // k_m(f)(x) = 0    if not
    // 
    // k_m(f) = f - Rf(f-1)
    //  Rf(f-1): Reconstruction of f by f-1 (f-1 < f)
    //  R*f(f+1): Dual reconstruction of f by f+1 (f<f+1)
    // k_mf(x) = 1 iff x in m(f)
    // k_mf(x) = 0 if not.
    //
    INIReader ini(szIni);

    if (ini.ParseError() != 0)
    {
        printf("Read failed\r\n");
        return 0;
    }

    int xi;
    int zi;
    
    xi = ini.GetInteger("watershed", "xi", -1);
    zi = ini.GetInteger("watershed", "zi", -1);
    // Rf; f-1;

    img_subtr_1 = img -1 ;
    inRange(img, Scalar(0), Scalar(zi), imgZi);
    inRange(img_subtr_1, Scalar(xi), Scalar(255), imgXi_1);
    inRange(img, Scalar(xi), Scalar(255), imgXi);

    imshow("Section Xi", imgXi);
    imshow("Section Xi-1", imgXi_1);
    imshow("Section Zi", imgZi);

    // Calculate Reconstruction
    labels = Mat(imgXi.size(), CV_16SC1, Scalar(0));
    imgRf_f_1 = Mat::zeros(imgXi.size(), imgXi.type());

    //
    // Wide-speading / numerate connected region
    //
    int labelID = 0;
    std::queue<cv::Point> queue;

    int aDX[4] = { 1, 0, -1, 0 };
    int aDY[4] = { 0, 1, 0, -1 };

    printf("Size=(%d,%d)\r\n", imgXi.rows, imgXi.cols);
    int count_scan = 0;

    for (int y=0; y<imgXi.rows; ++y)
    {
        for (int x=0; x<imgXi.cols; ++x)
        {
            if (imgXi.at<uchar>(y,x) > 0 && labels.at<int>(y,x) == 0)   // p in X[i](f)
            {
                // Start Wide-spreading
                labelID++;      // New label mark
                queue.push(Point(x,y));

                while (!queue.empty())
                {
                    Point p = queue.front();
                    queue.pop();

                    labels.at<int>(p.y, p.x) = labelID;
                    count_scan++;
                    
                    for (int idx=0;idx<4;idx++)
                    {
                        int go_x = p.x + aDX[idx];
                        int go_y = p.y + aDY[idx];

                        if (go_x >=0 && go_x < imgXi.cols && go_y >= 0 && go_y < imgXi.rows && 
                                labels.at<int>(go_y,go_x) == 0 && imgXi.at<uchar>(go_y, go_x) > 0)
                        {
                            // printf("HERE\r\n");
                            queue.push(Point(go_x, go_y));
                            labels.at<int>(go_y, go_x) = labelID;
                            count_scan++;
                        }
                    }
                }
            }
            else
            {
            }
        }
    }

    imshow("Labels", labels);
    printf("Scan-count-labeled=%d\r\n",count_scan);
    printf("Total Label=%d\r\n", labelID);

    // Calculate the Reconstruction (R[f](f-1))
    // R[f]_(f-1) <=> Rxif_(xif-1) = { x in x[i](f); E y in x[i](f-1); dX[i](f)(x,y) finite}
    imgRf_f_1 = Mat::zeros(imgXi.size(), imgXi.type());

    printf("Start Flooding");

    printf("Press u for inc Flooding; d for decrease Flooding\r\n");
    printf("Press U for inc(+10) Flooding; d for decrease(-10) Flooding\r\n");
    printf("ESC for exit\r\n");


    inRange(img, Scalar(xi), Scalar(255), imgXi);
    inRange(img, Scalar(0), Scalar(xi-1), imgZi);
    printf("Current Flooding=%d\r\n", xi);
    imshow("Flooding Xi", imgXi);
    imshow("Flooding Zi", imgZi);

    for (;;)
    {
        char c = waitKey();
        int old_xi = xi;

        if (c == 'u')
        {
            if (xi + 1 < 255)
            {
                xi++;
            }
        }
        else if (c=='d')
        {
            if (xi - 1 > 0)
            {
                xi--;
            }
        }
        else if (c == 'U')
        {
            if (xi + 10 < 255)
            {
                xi += 10;
            }
        }
        else if (c == 'D')
        {
            if (xi - 10 > 0)
            {
                xi -= 10;
            }
        }
        else if (c==27)
        {
            break;
        }

        if (old_xi != xi)
        {
            inRange(img, Scalar(xi), Scalar(255), imgXi);
            inRange(img, Scalar(0), Scalar(xi-1), imgZi);
            printf("Current Flooding=%d\r\n", xi);
            imshow("Flooding Xi", imgXi);
            imshow("Flooding Zi", imgZi);
        }
    }


    /*
    for (int y=0; y<imgRf_f_1.rows; ++y)
    {
        for (int x = 0; x<imgRf_f_1.cols; ++x)
        {
            if (imgXi.at<uchar>(y,x) > 0)
            {
                bool finite = false;
                int findID = labels.at<int>(y, x);

                for (int y1=0; y1<imgXi.rows; ++y1)
                {
                    for (int x1=0; x1 < imgXi.cols; ++x1)
                    {
                        if (imgXi_1.at<uchar>(y1,x1) > 0 &&  labels.at<uchar>(y1,x1) == findID)
                        {
                            finite = true;
                            break;
                        }
                    }

                    if (finite)
                    {
                        break;
                    }
                }

                imgRf_f_1.at<uchar>(y,x) = finite ? 255 : 0;
            }
        }
    }

    imshow("Reconstruction function (f) by (f-1)", imgRf_f_1);
    */

    waitKey();
    return 0;
}

int CPoultryMonitorApp::run_video_seg(const char* szFile, const char* szFolderTemp)
{
    VideoCapture video(szFile);

    if (!video.isOpened())
    {
        printf("Video could not opened\r\n");
        return -1;
    }

    vector<string> vFile;
    vector<Mat> vTemp;
    vector<Mat> vResTmpl;
    vector<Mat> vMask;      // Mask
    
    // Find Mask and Template


    bool use_mask = false;
    bool accept_mask;
    int match_method = TM_SQDIFF;
    int video_w;
    int video_h;

    IFileUtilPtr fup = std::make_shared<CFileUtil>();
    fup->getAllFileInFolder(szFolderTemp, vFile);

    video_w = video.get(CAP_PROP_FRAME_WIDTH);
    video_h = video.get(CAP_PROP_FRAME_HEIGHT);
    for (int i=0; i<vFile.size(); ++i)
    {
        printf("File=%s\r\n", vFile[i].c_str());
        Mat aImg = imread(vFile[i], IMREAD_COLOR);

        if (!aImg.empty())
        {
            vTemp.push_back(aImg);

            Mat aResTmpl;
            aResTmpl.create( video_w - aImg.cols + 1, 
                                video_h - aImg.rows +1, CV_32FC1);
            vResTmpl.push_back(aResTmpl);
        }
    }

    printf("Template count=%d\r\n", vTemp.size());
    printf("Width=%d,Height=%d,FPS=%d\r\n", 
                    (int) video.get(CAP_PROP_FRAME_WIDTH), 
                    (int) video.get(CAP_PROP_FRAME_HEIGHT),
                    (int) video.get(CAP_PROP_FRAME_COUNT));
    Mat frame;
    Mat frameHSV;
    Mat frameIR;
    Mat mask;
    double minVal; 
    double maxVal; 
    Point minLoc; 
    Point maxLoc;
    Point matchLoc;
    vector<int> compression_params;
    VideoWriter videoOut;
    int ex = static_cast<int>(video.get(CAP_PROP_FOURCC)); 
    
    compression_params.push_back( CV_IMWRITE_JPEG_QUALITY );
    compression_params.push_back( 100 );

    namedWindow("Video", WINDOW_AUTOSIZE);

    videoOut.open("out.avi", 
                    ex, 
                    video.get(CAP_PROP_FPS),
                    Size(video_w, video_h),
                    true);
    
    vector<Rect> vRc;
    int index=0;
    for (;;)
    {
        video >> frame;
        index++;

        if (frame.empty())
        {
            break;
        }

        // Template matching here
        if (index % 10 == 1)
        {
            vRc.clear();
            for (int i=0; i<vTemp.size(); ++i)
            {
                accept_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
                if (use_mask && accept_mask)
                {
                    matchTemplate( frame, vTemp[i], vResTmpl[i], match_method, mask);
                }
                else
                {
                    matchTemplate( frame, vTemp[i], vResTmpl[i], match_method);
                }

                normalize(vResTmpl[i], vResTmpl[i], 0, 1, NORM_MINMAX, -1, Mat());
                minMaxLoc(vResTmpl[i], &minVal, &maxVal, &minLoc, &maxLoc, Mat());

                if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
                { 
                    matchLoc = minLoc; 
                }
                else
                { 
                    matchLoc = maxLoc; 
                }  

                vRc.push_back(Rect(matchLoc.x, matchLoc.y, vTemp[i].cols, vTemp[i].rows));
                
                /*
                rectangle(frame, matchLoc, 
                                Point(matchLoc.x + vTemp[i].cols, matchLoc.y + vTemp[i].rows),
                                Scalar(0, 255, 255),
                                // Scalar(0, (18 + i * 73) % 255, (65 + i * 39) % 255),
                                2, 8, 0);
                */
            }
        }
        
        for (int i=0;i<vRc.size();++i)
        {
            rectangle(frame, vRc[i], Scalar(0, 255, 255), 2, 8, 0);
        }
        
        imshow("Video", frame);
        videoOut << frame;

        char c = (char)waitKey(25);
        if (c == 27) break;
    }

    printf("Finish");
    waitKey();
    return 0;
}

int CPoultryMonitorApp::grouping_flocks(std::vector<cv::Rect> vPoultry, std::vector<int>& vLabel)
{
    int mean_w;
    int mean_h;
    int sum_w;
    int sum_h;
    int n;

    double eps_w;   // epsilon width
    double eps_h;   // epsilon height

    vector<Point> vCenter;

    for (int i=0; i<vPoultry.size(); ++i)
    {
        sum_w += vPoultry[i].width;
        sum_h += vPoultry[i].height;

        vCenter.push_back(Point(vPoultry[i].x + vPoultry[i].width / 2,
                                vPoultry[i].y + vPoultry[i].height / 2));
    }

    mean_w = sum_w / vPoultry.size();
    mean_h = sum_h / vPoultry.size();
    eps_w = sum_w * 1.1 / vPoultry.size();
    eps_h = sum_h * 1.1 / vPoultry.size();

    //
    // Build a graph
    //
    vector<vector<int>> graph;
    
    // Building a graph
    n = graph.size();
    for (int i=0; i<n; ++i)
    {
        graph.push_back(vector<int>());
        for (int j=0; j<n; ++j)
        {
            graph[i][j] = 0;
        }
    }   

    for (int i=0; i<n; ++i)
    {
        for (int j=i+1; j<n; ++j)
        {
            if (abs(vCenter[i].x - vCenter[j].x) <= eps_w && 
                abs(vCenter[i].y - vCenter[j].y) <= eps_h)
            {
                graph[i][j] = 1;
                graph[j][i] = 1;
            }
        }
    }

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            if(graph[i][j] = 1)
            {
                // Find connected components 
            }
        }
    }

    return 0;
}