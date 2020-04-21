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

    // 
    // Extract every characters
    // Extract every characters
    

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


    //
    // Finding the connected components
    // 
    cv::Mat img_font = imread("/home/jcm/Pictures/opencv/abyssinica_font.png", IMREAD_COLOR);
    cv::Mat img_font_gray;
    cv::Mat img_connected;

    if (img_font.empty())
    {
        printf("READ FAILED\r\n");
    }

    if (img_font.channels() > 1)
    {
        // cvtColor(img_font, img_font_gray, COLOR_BGR2GRAY);
    }
    else
    {
        img_font_gray = img_font;
    }
    
    /*
    int n = connectedComponents(img_font_gray, img_connected);
    printf("Return = %d\r\n", n);
    printf("Connected size=(%d,%d)\r\n", img_connected.cols, img_connected.rows);
    const char* szImgGray = "Font gray";
    const char* szConnected = "Connected components";

    namedWindow(szImgGray, WINDOW_AUTOSIZE);
    namedWindow(szConnected, WINDOW_AUTOSIZE);
    imshow(szImgGray, img_font_gray);
    imshow(szConnected, img_connected);
    */

    // Dump 
    printf("aaaaaaaaaaaaaaaaaaaaa\r\n");
    cv::Mat img2 =  imread("/home/jcm/Pictures/opencv/bitstream_vera_sans_font_lowercase.png", IMREAD_COLOR);
    int step = img2.cols / 26;

    for (int ch = 0; ch < 25; ++ch)
    {
        cv::Mat imgChar = img2(cv::Rect( ch * step, 0, step, img2.rows));
        std::string file = "/home/jcm/Pictures/opencv/letters/char_"  + (char)(ch + 'a');
        file += ".png";

        imwrite(file, imgChar);
    }

    // 
    //@@ Collects characters
    // 
    


    waitKey();
    return 0;
}