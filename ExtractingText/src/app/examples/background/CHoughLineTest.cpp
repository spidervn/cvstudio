#include "CHoughLineTest.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

CHoughLineTest::CHoughLineTest()
{}

CHoughLineTest::~CHoughLineTest()
{}

int CHoughLineTest::run(int argc, char const* argv[])
{
    cv::Mat img;
    img = imread(argv[1], IMREAD_GRAYSCALE);

    if (img.empty())
    {
        printf("Image Empty\r\n");
        return -1;
    }


    /*
     * Approaches 
     *      A01: Scan all lines 
     *      A02: 
     */
    // 
    // Scan all lines 
    // 
    //
    // Re-implement Houghlines
    //
    //  Re-implement Houghlines 

    //
    //  Build Lines
    //
    // 
    // Probablistic HoughLine transform
    // 
    for (int y=0;y<img.rows;++y)
    {
        for (int x=0; x<img.cols;++x)
        {
            img.at<uchar>(y,x);
        }
    }


    return 0;
}