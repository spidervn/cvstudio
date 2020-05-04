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
    cv::Mat img_blur;
    cv::Mat img_detect;
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

    // Canny Edge first
    int lowThreshold = 40;
    int kernel_size = 3;

    blur(img, img_blur, Size(3,3));
    cv::Canny(img_blur, img_detect, lowThreshold, lowThreshold*3, kernel_size);

    /*
    for (int y=0;y<img.rows;++y)
    {
        for (int x=0; x<img.cols;++x)
        {
            img.at<uchar>(y,x);

            // 
            // File system
            // 


        }
    }
    */

    for (int y=0; y<img_detect.rows;++y)
    {
        for(int x=0; x<img_detect.cols;++x)
        {
            if (img_detect.at<uchar>(y,x) == 255)
            {

            }
        }
    }


    // Build a graph
    double step = 0.01;
    double startPI = 0;

    int x0 = 100;
    int y0 = 100;
    
    for (;startPI < CV_PI;startPI+=step)
    {
        double r = x0 * cos(startPI) + y0 * sin(startPI);
    }


    waitKey(0);
    return 0;
}