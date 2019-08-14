#include "CBanknoteStainedApp.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

CBanknoteStainedApp::CBanknoteStainedApp()
{}

CBanknoteStainedApp::~CBanknoteStainedApp()
{}

int CBanknoteStainedApp::run(int argc, char const *argv[])
{
    // Load image
    cv::Mat img;
    cv::Mat img_Gray;
    const char* szWin = "Window-gray";

    img = cv::imread(argv[1], IMREAD_COLOR);
    cvtColor(img, img_Gray, CV_BGR2GRAY);

    /* Distance transform */
    /* */

    /* Distance-transform */
    
    

    namedWindow(szWin, WINDOW_AUTOSIZE);
    imshow(szWin, img_Gray);

    waitKey();
    return 0;
}