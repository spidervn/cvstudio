#include "CPoultryMonitorApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <iostream>

using namespace cv;
using namespace std;

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
    return run_watershed(argv[1]);
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