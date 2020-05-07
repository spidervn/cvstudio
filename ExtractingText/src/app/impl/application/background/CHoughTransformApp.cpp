#include "CHoughTransformApp.h"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

CHoughTransformApp::CHoughTransformApp()
{}

CHoughTransformApp::~CHoughTransformApp()
{}

int CHoughTransformApp::run(int argc, char const* argv[])
{

    Mat img;
    Mat img_blur;

    img = imread(argv[1], IMREAD_COLOR);
    // Canny Edge


    //
    //
    //

    return 0;
}