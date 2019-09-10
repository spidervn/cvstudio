#include "CColorizeApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

CColorizeApp::CColorizeApp()
{}

CColorizeApp::~CColorizeApp()
{}

int CColorizeApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        return 0;
    }

    Mat img = imread(argv[1], IMREAD_GRAYSCALE);

    if (img.empty())
    {
        printf("Failed\r\n");
        return -1;
    }

    Mat imgColor;
    // cvtColor(img, imgColor, COLOR_GRAY2BGR);
    applyColorMap(img, imgColor, COLORMAP_RAINBOW);

    const char* szImg = "Img";
    const char* szImgColor = "Color";

    namedWindow(szImg, WINDOW_AUTOSIZE);
    namedWindow(szImgColor, WINDOW_AUTOSIZE);

    imshow(szImg, img);
    imshow(szImgColor, imgColor);

    

    waitKey();
    return 0;
}