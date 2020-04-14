#include "CPencilingApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <app/impl/cv/CCVCore.h>

using namespace std;
using namespace cv;

CPencilingApp::CPencilingApp(/* args */)
{
}

CPencilingApp::~CPencilingApp()
{
}

int CPencilingApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: penciling <<image>>\r\n");
        return -1;
    }

    const char* szImg = "img";    
    const char* szImgIvt = "img inverted";
    const char* szBlur = "Gaussian blur";
    const char* szDodge = "Dodge";
    const char* szDodgeIvt = "DodgeIvt";

    cv::Mat img;
    cv::Mat imgIvt;
    cv::Mat imgBlur;
    cv::Mat imgDodge;
    cv::Mat img2;
    
    img = imread(argv[1], IMREAD_GRAYSCALE);
    imgIvt = 255 - img;
    
    cv::GaussianBlur(imgIvt, imgBlur, cv::Size(5,5), 5);
    printf("----- Penciling\r\n");

    ICVCorePtr cvp = CCVCorePtrNew;
    printf("HERE00\r\n");
    cvp->dodge(imgBlur, imgIvt, imgDodge);
    printf("HERE\r\n");
    img2 = 255 - imgDodge;

    imshow(szImg, img);
    imshow(szImgIvt, imgIvt);
    imshow(szBlur, imgBlur);
    imshow(szDodge, imgDodge);
    imshow(szDodgeIvt, img2);

    waitKey();
    return 0;
}