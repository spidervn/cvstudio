#include "COrientedStrokeDetect.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

COrientedStrokeDetect::COrientedStrokeDetect(/* args */)
{
}

COrientedStrokeDetect::~COrientedStrokeDetect()
{
}

int COrientedStrokeDetect::run(int argc, const char* argv[])
{
    /*
        Gradient projection:
            G[a,s] = dR[a]R[s]I/dx
     */
    // Gradient projection
    // D subset N^2 -> [0,1]
    // D subset N^2 -> [0,1]
    
    cv::Mat img = imread(argv[1], IMREAD_GRAYSCALE);

    cv::Mat mmatrix = (cv::Mat_<double>(2,3) << 
        0.25, 0.0, 0.0,
        0.0, 0.25, 0.0
    );

    Mat rot_mat = getRotationMatrix2D(cv::Point(img.rows/2 ,img.cols/2), 0, 0.25);
    Mat dst = Mat::zeros(img.rows, img.cols, img.type());

    cout << "Matrix "  << mmatrix << endl;
    cout << "Matrix2 " << rot_mat << endl;

    cv::Mat warpOut;
    cv::warpAffine(img, warpOut, mmatrix, img.size() );

    imshow("src", img);
    imshow("dst", warpOut);
    waitKey();
    return 0;
}

cv::Mat COrientedStrokeDetect::F(double a, double b)
{
    cv::Mat m = (cv::Mat_<double>(5,5) << 
        a, a, 0.0, b, b,
        a, a, 0.0, b, b,
        a, a, 0.0, b, b, 
        a, a, 0.0, b, b,
        a, a, 0.0, b, b
    );
    return m;
}

cv::Mat COrientedStrokeDetect::thresholdToZero(cv::Mat inp, double threshold)
{
    //
    //  inp[y,x] = inp[y,x] if inp[y,x] >= threshold
    //  inp[y,x] = 0, otherwise
    // 
    cv::Mat dst;
    cv::threshold(
        inp,
        dst,
        threshold,
        255,
        CV_THRESH_TOZERO
    );

    return dst;
}

void COrientedStrokeDetect::calcResponse(cv::Mat inp, cv::Mat& out)
{
    cv::Mat dst;
    cv::Mat max01;
    cv::Mat max02;

    cv::filter2D(inp, dst, inp.depth(), F(-1.0,1.0));

    // 
    // Warp affine transformation.
    // 

    // Scale? 

    
}