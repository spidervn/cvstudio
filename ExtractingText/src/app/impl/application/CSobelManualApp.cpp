#include "CSobelManualApp.h"
#include "app/impl/cv/CCVCore.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <memory>

using namespace std;
using namespace cv;

CSobelManualApp::CSobelManualApp()
{

}
CSobelManualApp::~CSobelManualApp()
{

}

int CSobelManualApp::run(int argc, char const *argv[])
{
    shared_ptr<ICVCore> p = make_shared<CCVCore>();

    if (argc < 2)
    {
        printf("Usage: %s <<image>>\r\n", argv[0]);
        return -1;
    }

    Mat dst;
    Mat dstCv;  // Sobel CV
    Mat grad;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat img = imread(argv[1], IMREAD_ANYCOLOR);

    if (img.empty())
    {
        printf("Invalid image\r\n");
    }
    else
    {
        const char* szSource = "Source";
        const char* szSobel = "Sobel";
        const char* szCvSobel = "cvSobel";

        printf("Before sobel\r\n");
        printf("Done sobel\r\n");
        p->sobel(img, dst);

        cv::Sobel(img, grad_x, img.depth(), 1, 0);
        cv::Sobel(img, grad_y, img.depth(), 0, 1);
        
        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

        namedWindow(szSource, WINDOW_AUTOSIZE);
        namedWindow(szSobel, WINDOW_AUTOSIZE);
        namedWindow(szCvSobel, WINDOW_AUTOSIZE);
        
        imshow(szSource, img);
        imshow(szSobel, dst);
        imshow(szCvSobel, grad);

        waitKey();
    }

    return 0;
}