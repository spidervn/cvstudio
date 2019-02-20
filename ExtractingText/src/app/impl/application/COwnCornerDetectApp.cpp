#include "COwnCornerDetectApp.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

#define SHITOMASHI_WINDOW "My Shi Tomasi corner detector"
#define HARRIS_WINDOW "My Harris corner detector"

COwnCornerDetectApp::COwnCornerDetectApp(/* args */)
{
}

COwnCornerDetectApp::~COwnCornerDetectApp()
{
}

int COwnCornerDetectApp::run(int argc, char const *argv[])
{
    myShiTomasi_qualityLevel = 50;
    myHarris_qualityLevel = 50;
    max_qualityLevel = 100;

    CommandLineParser parser( argc, argv, "{@input | ../data/building.jpg | input image}");
    src = imread( parser.get<String>( "@input" ) );
    if ( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    int blockSize = 3;
    int apertureSize = 3;
    
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    cornerEigenValsAndVecs(src_gray, myHarris_dst, blockSize, apertureSize);

    /* calculate Mc */
    Mc = Mat(src_gray.size(), CV_32FC1);
    for( int i = 0; i < src_gray.rows; i++ )
    {
        for( int j = 0; j < src_gray.cols; j++ )
        {
            float lambda_1 = myHarris_dst.at<Vec6f>(i, j)[0];
            float lambda_2 = myHarris_dst.at<Vec6f>(i, j)[1];

            Mc.at<float>(i,j) = lambda_1 * lambda_2 - 0.04f * pow( (lambda_1 + lambda_2), 2 );
        }
    }

    minMaxLoc(Mc, &myHarris_minVal, &myHarris_maxVal);

    namedWindow(HARRIS_WINDOW);
    createTrackbar("Quality Level", HARRIS_WINDOW, &myHarris_qualityLevel, max_qualityLevel, OnTrackbarHarris, (void*)this);
    OnTrackbarHarris(0, (void*)this);

    cornerMinEigenVal(src_gray, myShiTomasi_dst, blockSize, apertureSize);
    // minMaxLoc(myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_qualityLevel, max_qualityLevel, OnTrackbarShiTomasi, (void*)this);
    minMaxLoc( myShiTomasi_dst, &myShiTomasi_minVal, &myShiTomasi_maxVal);

    namedWindow(SHITOMASHI_WINDOW);
    createTrackbar("Quality Level:", SHITOMASHI_WINDOW, &myShiTomasi_qualityLevel, max_qualityLevel, OnTrackbarShiTomasi, (void*)this);
    OnTrackbarShiTomasi(0, (void*)this);

    waitKey();
    return 0;
}

int COwnCornerDetectApp::myHarrisFunc(int, void*)
{
    myHarris_cpy = src.clone();
    myHarris_qualityLevel = MAX(myHarris_qualityLevel, 1);

    for(int i = 0; i < src_gray.rows; i++)
    {
        for(int j = 0; j < src_gray.cols; j++)
        {
            if (Mc.at<float>(i,j) > myHarris_minVal + (myHarris_maxVal - myHarris_minVal) * myHarris_qualityLevel/max_qualityLevel)
            {
                circle(myHarris_cpy, Point(j,i), 4, Scalar( rng.uniform(0,256), rng.uniform(0,256), rng.uniform(0,256)), FILLED);
            }
        }
    }

    imshow(HARRIS_WINDOW, myHarris_cpy);    
    return 0;
}

int COwnCornerDetectApp::myShiTomasiFunc(int, void*)
{
    myShiTomasi_cpy = src.clone();
    myShiTomasi_qualityLevel = MAX(myShiTomasi_qualityLevel, 1);

    for (int i=0;i<src_gray.rows;i++)
    {
        for (int j=0; j<src_gray.cols;j++)
        {
            if (myShiTomasi_dst.at<float>(i,j) > myShiTomasi_minVal + (myShiTomasi_maxVal - myShiTomasi_minVal) * myShiTomasi_qualityLevel / max_qualityLevel)
            {
                circle(myShiTomasi_cpy, Point(j,i), 4, Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0,256)), FILLED);
            }
        }
    }

    imshow(SHITOMASHI_WINDOW, myShiTomasi_cpy);
    return 0;
}

void COwnCornerDetectApp::OnTrackbarHarris(int nData,void* pData)
{
    if (pData != NULL)
    {
        COwnCornerDetectApp* pApp = (COwnCornerDetectApp*)pData;
        pApp->myHarrisFunc(nData, NULL);
    }

}

void COwnCornerDetectApp::OnTrackbarShiTomasi(int nData,void* pData)
{
    if (pData != NULL)
    {
        COwnCornerDetectApp* pApp = (COwnCornerDetectApp*)pData;
        pApp->myShiTomasiFunc(nData, NULL);
    }
}