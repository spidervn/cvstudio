#include "CHistogramCalcApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


CHistogramCalcApp::CHistogramCalcApp()
{

}


CHistogramCalcApp::~CHistogramCalcApp()
{

}


int CHistogramCalcApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Calculate histogram: %s <<img_name>>\r\n", argv[0]);
        return 0;
    }

    Mat src = imread(argv[1], IMREAD_COLOR);
    Mat dst;

    

    return 0;
}