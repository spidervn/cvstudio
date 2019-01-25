#include "CHistogramEqApp.h"
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

CHistogramEqApp::CHistogramEqApp()
{}

CHistogramEqApp::~CHistogramEqApp()
{}

int CHistogramEqApp::run(int argc, char const *argv[])
{
    printf("Histogram EQ\r\n");
    if (argc < 2)
    {
        printf("Usage: histogrameq <<img_name>>\r\n");
        return 0;
    }

    Mat src = imread(argv[1], IMREAD_COLOR);
    Mat dst;

    // cvtColor(src, src, COLOR_BGR2GRAY);
    equalizeHist(src, dst);

    imshow("Source image", src);
    imshow("Equalized Image", dst);

    waitKey();
    return 0;
}
