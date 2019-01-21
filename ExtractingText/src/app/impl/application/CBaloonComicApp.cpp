#include "CBaloonComicApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

CBaloonComicApp::CBaloonComicApp()
{}

CBaloonComicApp::~CBaloonComicApp()
{}

int CBaloonComicApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("BaloomComic <<file_name>>\r\n");
        return 0;
    }
    
    Mat img = imread(argv[1], IMREAD_COLOR);
    Mat img_Out;

    cvtColor(img, img_Out, COLOR_BGR2GRAY);

    namedWindow("HI", WINDOW_AUTOSIZE);
    imshow("HI", img_Out);

    waitKey(0);
    return 0;
}
