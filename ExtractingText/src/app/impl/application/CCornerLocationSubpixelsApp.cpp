#include "CCornerLocationSubpixelsApp.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

#define CORNER_LOC_SUBPIXELS_WINDOW "Image"

CCornerLocationSubpixelsApp::CCornerLocationSubpixelsApp(/* args */)
{}

CCornerLocationSubpixelsApp::~CCornerLocationSubpixelsApp()
{}

int CCornerLocationSubpixelsApp::run(int argc, char const *argv[])
{
    CommandLineParser parser( argc, argv, "{@input | ../data/pic3.png | input image}" );
    src = imread( parser.get<String>( "@input" ) );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    maxCorners = 10;
    maxTrackbar = 25;
    rng = RNG(12345);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);    // Convert Image to Gray
    namedWindow(CORNER_LOC_SUBPIXELS_WINDOW);   // Prepare window for displaying image
    
    createTrackbar("Max corners:", CORNER_LOC_SUBPIXELS_WINDOW,
                        &maxCorners,
                        maxTrackbar,
                        OnTrackbarCallback,
                        (void*)this);
    
    imshow(CORNER_LOC_SUBPIXELS_WINDOW, src);
    OnTrackbarCallback(0, (void*)this);

    waitKey();
    return 0;
}

void CCornerLocationSubpixelsApp::fncFeaturesToTrack(int nData, void* pData)
{
    
    maxCorners = MAX(maxCorners , 1);
    vector<Point2f> corners;

    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    int gradientSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;

    Mat copy = src.clone();

    goodFeaturesToTrack(src_gray,
                        corners,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        gradientSize,
                        useHarrisDetector,
                        k);

    cout << "Number of corners detected: " << corners.size() << endl;
    int radius = 4;
    for(size_t i = 0; i < corners.size(); i++)
    {
        circle(copy, corners[i], radius, Scalar(rng.uniform(0,255), rng.uniform(0,256), rng.uniform(0,256)), FILLED);
    }

    namedWindow(CORNER_LOC_SUBPIXELS_WINDOW);
    imshow(CORNER_LOC_SUBPIXELS_WINDOW, copy);

    Size winSize = Size(5, 5);
    Size zeroZone = Size(-1, -1);
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);

    cornerSubPix(src_gray, corners, winSize, zeroZone, criteria);
    for(size_t i = 0; i < corners.size(); i++)
    {
        cout << " -- Refined corner [" << i << "] (" << corners[i].x << "," << corners[i].y << ")" << endl;
    }    
}

void CCornerLocationSubpixelsApp::OnTrackbarCallback(int nData, void* pData)
{
    if (pData != NULL)
    {
        CCornerLocationSubpixelsApp* pApp = (CCornerLocationSubpixelsApp*) pData;
        pApp->fncFeaturesToTrack(nData, pData);
    }
}