#include "CImgResizingApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

CImgResizingApp::CImgResizingApp()
{}

CImgResizingApp::~CImgResizingApp()
{}

int CImgResizingApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("%s <<image_file>>\r\n", argv[0]);
        return -1;
    }

    Mat img;
    Mat dst;
    img = imread(argv[1], IMREAD_COLOR);
    
    const char* szSource = "Source";
    const char* szResize = "Resize";

    namedWindow(szSource, WINDOW_AUTOSIZE);
    namedWindow(szResize, WINDOW_AUTOSIZE);

    cv::resize(img, dst, cv::Size(), 2.2, 2.2, INTER_CUBIC);

    imshow(szSource, img);
    imshow(szResize, dst);
    
    waitKey();
    return 0;
}