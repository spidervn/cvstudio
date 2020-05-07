#include "CHoughLineTest.h"
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>
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
    cv::Mat img_color;
    cv::Mat img;
    cv::Mat img_blur;
    cv::Mat img_detect;
    cv::Mat mat_accumulator;

    img = imread(argv[1], IMREAD_GRAYSCALE);
    img_color = imread(argv[1], IMREAD_COLOR);

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
    imshow("canny", img_detect);

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

    //
    // Min R = 
    // 
    // mat_accumulator.create();   // 2R * 90
    // R = ?
    double R = sqrt(img_detect.rows * img_detect.rows + img_detect.cols + img_detect.cols);
    // mat_accumulator.create(cv::Size((int)R, 90), CV_64FC1);
    mat_accumulator = Mat::zeros((int)R, 90, CV_64FC1);

    int threshold = 5;

    for (int y=0; y<img_detect.rows;++y)
    {
        for(int x=0; x<img_detect.cols;++x)
        {
            if (img_detect.at<uchar>(y,x) == 255)
            {
                // Detected lines
                // Build Graph

                double step = CV_PI / 90;
                double theta = 0;
                for (int i=0; i<90; ++i)
                {
                    double theta = i * step;
                    double r = (double)x * cos(theta) + (double)y*sin(theta);

                    mat_accumulator.at<double>((int)r, i) = mat_accumulator.at<double>((int)r, i) + 1;
                }

            }
        }
    }   


    // Find 05 top most 
    double max = 0;
    int rrow;
    int rcol;
    for (int y=0; y<img_detect.rows;++y)
    {
        for(int x=0; x<img_detect.cols;++x)
        {
            if (mat_accumulator.at<double>(y,x) > max)
            {
                max = mat_accumulator.at<double>(y,x);
                rrow = y;
                rcol = x;

            }
        }
    }

    // 
    // Print ()
    // 
    if (rcol == 0)
    {
        cv::line(
            img_color,
            cv::Point(0,(int)rrow),
            cv::Point(img_color.rows-1,(int)rrow),
            Scalar(0,255,255),
            1,
            LINE_8);
    }
    else
    {
        double theta = rcol * CV_PI/90;
        double y0 = rrow/sin(theta);
        double y1 = -(double)(img_color.cols)/tan(theta) + rrow/sin(theta);

        cv::Point p0(y0, 0);
        cv::Point p1(y1, img_color.cols);

        cv::line(img_color,
            p0,
            p1,
            Scalar(0,255,255),
            1,
            LINE_8);
    }
    imshow("line", img_color);

    waitKey(0);
    return 0;
}