#include "CPoultryMonitorApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

CPoultryMonitorApp::CPoultryMonitorApp()
{}

CPoultryMonitorApp::~CPoultryMonitorApp()
{}

int CPoultryMonitorApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    int morph_size = 1;
    Mat img = imread(argv[1]);
    Mat imgGray;
    Mat dst;
    Mat dstOpen;
    Mat element = getStructuringElement( MORPH_RECT, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );    

    cvtColor(img,imgGray, COLOR_BGR2GRAY);
    threshold(imgGray, dst, 155, 255, THRESH_BINARY);

    morphologyEx(dst, dstOpen, cv::MORPH_OPEN, element);

    // Thresholding
    const char* szImgGray = "Gray";
    const char* szThreshold = "Threshold";
    const char* szOpening = "Openning";

    namedWindow(szImgGray, WINDOW_AUTOSIZE);
    namedWindow(szThreshold, WINDOW_AUTOSIZE);
    namedWindow(szOpening, WINDOW_AUTOSIZE);

    imshow(szImgGray, imgGray);
    imshow(szThreshold, dst);
    imshow(szOpening, dstOpen);

    waitKey();
    return 0;
}