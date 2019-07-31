#include "CExtractTextApp.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

CExtractTextApp::CExtractTextApp(/* args */)
{
}

CExtractTextApp::~CExtractTextApp()
{
}

int CExtractTextApp::run(int argc, char const *argv[])
{
    // Extract text Here
    // Load images
    //  1- Use thresholding to removing background
    //      Threshold to Zero
    //  2- Then extract every characters 
    //  3- Apply image segmentations

    

    cv::Mat img;
    cv::Mat img_gray;
    cv::Mat img_inv;
    cv::Mat dst;
    cv::Mat df;
    //1) Read
    img = imread(argv[1], IMREAD_COLOR);
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    img_inv = 255 - img_gray;

    threshold(img_inv, dst, 190, 255, THRESH_TOZERO);
    distanceTransform(dst, df, DIST_L2, 3);
    // 
    // Invert color 
    // Thresholding? 
    // 
    const char* szInvert = "Invert color";
    const char* szThreshold = "Thresholding";
    const char* szDF = "Distance Tranform";

    namedWindow(szInvert,  WINDOW_AUTOSIZE);
    namedWindow(szThreshold,  WINDOW_AUTOSIZE);
    namedWindow(szDF, WINDOW_AUTOSIZE);
    
    imshow(szInvert, img_inv);
    imshow(szThreshold, dst);
    imshow(szDF, df);

    waitKey();
    return 0;
}