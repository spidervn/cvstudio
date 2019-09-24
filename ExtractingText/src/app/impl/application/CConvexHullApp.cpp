#include "CConvexHullApp.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

CConvexHullApp::CConvexHullApp(/* args */):rng(12345)
{
}

CConvexHullApp::~CConvexHullApp()
{
}

int CConvexHullApp::run(int argc, char const *argv[])
{
    printf("Usage convexhullapp <<image>>\r\n");

    cv::Mat img;

    src = imread(argv[1]);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3,3));

    const char* szWindow = "Source";
    namedWindow(szWindow);
    imshow(szWindow, src);

    const int max_thresh = 255;
    createTrackbar("Canny Thresh", szWindow, &thresh, max_thresh, OnThresholdCB, (void*)this);
    OnThresholdCB(0,this);

    waitKey();
    return 0;
}

void CConvexHullApp::OnThresholdCB(int,void* p_Data)
{
    if (p_Data != NULL)
    {
        CConvexHullApp* p_App = (CConvexHullApp*)p_Data;
        cv::Mat canny_output;
        Canny(p_App->src_gray, canny_output, p_App->thresh, p_App->thresh * 2);

        vector<vector<Point>> contours;
        findContours(canny_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

        vector<vector<Point>> hull(contours.size());
        for( size_t i = 0; i < contours.size(); i++ )
        {
            convexHull( contours[i], hull[i] );
        }

        Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( p_App->rng.uniform(0, 256), p_App->rng.uniform(0,256), p_App->rng.uniform(0,256) );
            drawContours( drawing, contours, (int)i, color);
            drawContours( drawing, hull, (int)i, color);
        }

        imshow( "Hull demo", drawing );
    }
}