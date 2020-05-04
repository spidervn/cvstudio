#include "CSmoothImgApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"

using namespace cv;
CSmoothImgApp::CSmoothImgApp()
{}

CSmoothImgApp::~CSmoothImgApp()
{}

int CSmoothImgApp::run(int argc, char const *argv[])
{
    cv::Mat img = imread(argv[1], IMREAD_COLOR);
    cv::Mat img_blur;
    cv::Mat img_median;

    if (img.empty())
    {
        printf("Could not load\n");
        return -1;
    }


    cv::medianBlur(img, img_median, 5);
    cv::blur(img, img_blur, cv::Size(5,5));

    imshow("img", img);
    imshow("median blur", img_median);
    imshow("normal blur", img_blur);

    waitKey();
    return 0;
}
