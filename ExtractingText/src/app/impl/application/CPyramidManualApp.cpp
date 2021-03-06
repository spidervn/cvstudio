#include "CPyramidManualApp.h"
#include "app/impl/cv/CCVCore.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

CPyramidManualApp::CPyramidManualApp()
{}

CPyramidManualApp::~CPyramidManualApp()
{}

int CPyramidManualApp::run(int argc, char const *argv[])
{
    //ICVCore* ccp = new CCVCore();
    ICVCorePtr ccp = std::make_shared<CCVCore>();

    if (argc < 2)
    {
        printf("Usage: pyramidManual <<image>>\r\n");
        return -1;
    }
    cv::Mat img;
    cv::Mat imgGauss;
    cv::Mat dst;
    cv::Mat dst2;
    cv::Mat dstUp;
    cv::Mat dstCvUp;

    img = imread(argv[1], IMREAD_COLOR);
    
    if (img.empty())
    {
        return -1;
    }

    cv::cvtColor(img, imgGauss, COLOR_BGR2HSV);

    cv::Mat gaussKernel = (cv::Mat_<double>(5, 5) << 1, 4, 6, 4, 1,
                                                        4, 16, 24, 16, 4,
                                                        6, 24, 36, 24, 6,
                                                        4, 16, 24, 16, 4,
                                                        1, 4, 6, 4, 1);

    gaussKernel = gaussKernel / 266; //(32 + 128 + 96);
    
    cv::filter2D(img, imgGauss, img.depth(), gaussKernel);

    ccp->gaussianPyramid(img, dst);
    ccp->gaussianPyramidUp(img, dstUp);

    pyrDown(img, dst2);
    pyrUp(img, dstCvUp);

    const char* szSource = "Source";
    const char* szGauss = "Gauss";
    const char* szManual = "Manual Pyramid";
    const char* szManualUp = "Manual Pyramid Up";
    const char* szCvPyramid = "CV Pyramid";
    const char* szCvPyramidUp = "CV Pyramid Up";

    namedWindow(szSource, WINDOW_AUTOSIZE);
    namedWindow(szGauss, WINDOW_AUTOSIZE);
    namedWindow(szManual, WINDOW_AUTOSIZE);
    namedWindow(szManualUp, WINDOW_AUTOSIZE);
    namedWindow(szCvPyramid, WINDOW_AUTOSIZE);
    namedWindow(szCvPyramidUp, WINDOW_AUTOSIZE);

    imshow(szSource, img);
    imshow(szGauss, imgGauss);
    imshow(szManual, dst);
    imshow(szManualUp, dstUp);
    imshow(szCvPyramid, dst2);
    imshow(szCvPyramidUp, dstCvUp);

    waitKey();

    // delete ccp;
    return 0;
}