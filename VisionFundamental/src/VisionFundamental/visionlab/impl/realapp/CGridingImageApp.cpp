#include "CGridingImageApp.h"
#include <opencv2/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

CGridingImageApp::CGridingImageApp(/* args */)
{
}

CGridingImageApp::~CGridingImageApp()
{
}

int CGridingImageApp::run(int argc, char const* argv[])
{
    cv::Mat img;
    img = imread(argv[1], IMREAD_COLOR);

    int DIVIDE = 10;

    if (!img.empty())
    {
        int w = img.cols;
        int h = img.rows;

        int w_step = w / DIVIDE;
        int h_step = h / DIVIDE;

        int g_step = std::min(w_step, h_step); // General step
        g_step = std::max(g_step, 10);

        int wcount = ceil(w/g_step);
        int hcount = ceil(h/g_step);

        for (int i=1; i< wcount; ++i)
        {
            cv::line(img,
                cv::Point(i*g_step, 0),
                cv::Point(i*g_step, h),
                cv::Scalar(192,192,192));
        }

        for (int j=1; j<hcount;++j)
        {
            cv::line(
                img,
                cv::Point(0, j*g_step),
                cv::Point(w, j*g_step),
                cv::Scalar(192,192,192)
            );
        }

        imshow("AASA", img);
        waitKey();
    }
    return 0;
}

