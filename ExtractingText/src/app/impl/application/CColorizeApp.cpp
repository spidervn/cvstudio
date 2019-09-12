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
    Mat imgRGB;
    Mat imgHSL;
    // cvtColor(img, imgColor, COLOR_GRAY2BGR);
    applyColorMap(img, imgColor, COLORMAP_RAINBOW);

    const char* szImg = "Img";
    const char* szImgColor = "Color";
    const char* szHSL = "HSL";


    namedWindow(szImg, WINDOW_AUTOSIZE);
    namedWindow(szImgColor, WINDOW_AUTOSIZE);
    namedWindow(szHSL, WINDOW_AUTOSIZE);

    imshow(szImg, img);
    imshow(szImgColor, imgColor);

    printf("A\r\n");
    cvtColor(img, imgRGB, COLOR_GRAY2BGR);
    cvtColor(imgRGB, imgHSL, COLOR_BGR2HSV);
    printf("A1\r\n");

    printf("HSL Image(channel=%d;)\r\n", imgHSL.channels());

    /*
    Mat_<Vec3b> I_ = imgHSL;
    for (int y=0; y< img.rows; ++y)
    {
        for (int x=0; x<img.cols;++x)
        {
            I_(y,x)[0] = img.at<uchar>(y,x);
            I_(y,x)[1] = 255 - I_(y,x)[1];
            // I_(y,x)[2] = (img.at<uchar>(y,x)*img.at<uchar>(y,x)) % 255;
        }
    }
    */
   
    imshow(szHSL, imgHSL);


    waitKey();
    return 0;
}