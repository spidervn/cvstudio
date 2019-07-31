#include "CExtractText.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

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
    //  2- 
    

    cv::Mat img;
    cv::Mat img_gray;
    cv::Mat img_inv;
    cv::Mat dst;
    //1) Read
    img = imread(argv[1], IMREAD_COLOR);
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    img_inv = 255 - img_gray;

    threshold(img_gray, dst, 100, 255, THRESH_TOZERO);

    const char* szInvert = "Invert color";
    const char* szThreshold = "Thresholding";

    namedWindow(szInvert,  WINDOW_AUTOSIZE);
    namedWindow(szThreshold,  WINDOW_AUTOSIZE);
    
    imshow(szInvert, img_inv);
    imshow(szThreshold, dst);

    waitKey();
    return 0;
}