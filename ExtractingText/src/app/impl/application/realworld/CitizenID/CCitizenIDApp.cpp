#include "CCitizenIDApp.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "app/impl/cv/CCVCore.h"
#include <iostream>

using namespace cv;
using namespace std;

CCitizenIDApp::CCitizenIDApp()
{}

CCitizenIDApp::~CCitizenIDApp()
{}

int CCitizenIDApp::run(int argc, char const* argv[])
{
    // 1st 
    //   * Align the Image
    //   * Implement HoughLine first
    //   * Then Alignment The text (Anti Rotation)  
    // * Align the Image
    //   * Implement HoughLine first.
    //   * 
    // 

    // HoughLine
    // HoughLine & perform 
    //  * Perform HoughLinesP

    Mat src = imread( argv[1], IMREAD_COLOR);
    Mat dst;
    Mat cdst;
    Mat cdstP;

    if (src.empty())
    {
        printf("invalid\r\n");
        return -1;
    }
    
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();

    // Standard HoughLine transform
    vector<Vec2f> lines;
    
    // 
    // @Find@ related images with reverse image search 
    // 
    
    Mat gray;
    Mat thresh;

    cv::cvtColor(src, gray, COLOR_BGR2GRAY);
    cv::bitwise_not(gray, gray);  // Black => white & white to black 
    cv::threshold(gray, thresh, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);   // Foreground to 255, background to 0

    imshow("thresh", thresh);

    vector<Point> points;
    for (int y=0; y<thresh.rows;++y)
    {
        for (int x=0; x<thresh.cols; ++x)
        {
            if (thresh.at<uchar>(y,x) > 0)
            {
                //points.push_back(cv::Point2i(x, y));
                points.push_back(cv::Point2i(y, x));
            }
        }
    }

    cv::RotatedRect rr = cv::minAreaRect(points);

    float angle;
    if (rr.angle < -45)
    {
        angle = -(90 - rr.angle);
    }
    else
    {
        angle = -rr.angle;
    }
    printf("Angles=%f; %f\r\n", rr.angle, angle);

    // cv::Mat M = cv::getRotationMatrix2D(cv::Point2f( thresh.cols/2, thresh.rows/2), angle, 1.0);
    cv::Mat M = cv::getRotationMatrix2D(cv::Point2f( thresh.rows/2, thresh.cols/2), angle, 1.0);
    cv::warpAffine(src, dst, M, cv::Size(src.cols, src.rows), INTER_CUBIC, BORDER_REPLICATE);

    ICVCorePtr ccptr = CCVCorePtrNew();
    cv::Mat gauss;
    ccptr->calc_Gaussian2DKernel(5, gauss);

    cout << "Gauss " << gauss << endl;

    Mat lowfreq;
    calc_low_frequency_image(gray, lowfreq, 5);
    
    printf("OK\r\n");
    imshow("input", src);
    imshow("rotated", dst);
    imshow("lowfreq", lowfreq);
    waitKey();

    // Face recognition
    return 0;
}

int CCitizenIDApp::calc_low_frequency_image(cv::Mat inp, cv::Mat& out, int ksize)
{
    Mat mgauss;
    //ICVCorePtr cvcp = CCVCorePtrNew();
    CCVCore cvc;
    cvc.calc_Gaussian2DKernel(ksize, mgauss);

    if (inp.channels() != 1)
    {
        printf("Invalid\r\n");
        return -1;
    }

    out.create(inp.size(), inp.type());
    Mat F = cv::Mat::zeros(cv::Size(ksize, ksize), CV_64FC1);
    Mat W = cv::Mat::zeros(cv::Size(ksize, ksize), CV_64FC1);
    uchar depth = inp.type() & CV_MAT_DEPTH_MASK;
    
    printf("HERE\r\n");
    for (int y=0; y<inp.rows;++y)
    {
        for (int x=0; x<inp.cols;++x)
        {
            printf("HERE(%d,%d)\r\n", y,x);
            double Ti = mean_a_subrange(inp, y, x, ksize);

            printf("Ti=%f\r\n", Ti);
            
            for (int ky=0; ky<W.rows;++ky)
            {
                for (int kx=0; kx<W.cols;++kx)
                {
                    W.at<double>(y,x) = inp.at<uchar>(y,x) < Ti ? 0 : 1;
                    F.at<double>(y,x) = W.at<double>(y,x) * mgauss.at<double>(y,x);
                }
            }

            if (depth == CV_8U || depth == CV_8S)
            {
                printf("TypeUChar");
                out.at<uchar>(y, x) = (uchar)convolve_element(inp, F, y, x);
            }
            else if (depth == CV_32S || depth == CV_32F)
            {
                printf("TypeInt");
                out.at<int>(y, x) = (uchar)convolve_element(inp, F, y, x);
            }
            else if (depth == CV_64F)
            {
                printf("TypeDouble");
                out.at<double>(y, x) = (uchar)convolve_element(inp, F, y, x);
            }
            else 
            {
                printf("No Datatype");
            }
        }
    }

    printf("Finish\r\n");
    imshow("lowf_out", out);
    waitKey();
    return 0;
}

double CCitizenIDApp::mean_a_subrange(cv::Mat inp, int y, int x, int ksize)
{
    double ret = 0.0;

    int x0;
    int y0;

    x0 = x - ksize/2;
    y0 = y - ksize/2;

    if (x0 <= 0) x0 = 0;
    if (y0 <= 0) y0 = 0;

    int w = min(ksize, inp.cols - x0);
    int h = min(ksize, inp.rows - y0);

    cv::Mat roi = cv::Mat(inp, cv::Rect(x0, y0, w, h));
    cv::Scalar mean = cv::mean(roi);
    return mean.val[0];
}

double CCitizenIDApp::convolve_element(cv::Mat inp, cv::Mat kernel, int y, int x, int kcenterx, int kcentery)
{
    double ret = 0.0;
    int cx;
    int cy;

    if (kcenterx == -1)
    {
        kcenterx = kernel.cols/2;
    }

    if (kcentery == -1)
    {
        kcentery = kernel.rows/2;
    }

    for (int irow=0; irow<kernel.rows;++irow)
    {
        for (int icol=0; icol<kernel.cols; ++icol)
        {
            int inpx = x + (icol - kcenterx);
            int inpy = y + (irow - kcentery);

            if (inpx >=0 && inpx < inp.cols && inpy >=0 && inpy < inp.rows)
            {
                ret += inp.at<uchar>(inpy, inpx) * kernel.at<double>(irow,icol);
            }
        }
    }

    return ret;
}