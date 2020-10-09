#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "visionfund/impl/CImgProcess.h"
#include "visionlab/impl/CLoadfontApp.h"
#include "visionlab/impl/CPaintbox.h"
#include "visionlab/impl/lab/CDeskewLab.h"

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    /*
    cv::Mat img = imread(argv[1], IMREAD_COLOR);
    cv::Mat img_gray;
    cv::Mat derivate;
    cv::Mat sobel;

    
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    Sobel(img_gray, sobel, img_gray.depth(), 3, 3, 5);

    IImgProcessPtr ipp = CImgProcessPtrNew;
    ipp->derivative(img_gray, derivate);

    imshow("src", img_gray);
    imshow("1st derivative", derivate);
    imshow("sobel", sobel);

    printf("size src=(%d,%d); derivative(%d,%d); sobel(%d,%d)\r\n", 
            img_gray.cols, img_gray.rows,
            derivate.cols, derivate.rows,
            sobel.cols, sobel.rows
    );

    waitKey();
    */

    //CLoadfontApp app;
    //app.run(argc, argv);

    /*
    cv::Mat img = Mat::zeros(cv::Size(800,600), CV_8UC3);

    IPaintboxPtr pbp = CPaintboxPtrNew;
    pbp->paintBoard(img, cv::Rect(20,20, 500,500));

    imshow("a", img);
    waitKey();
    */

    CDeskewLab lab;
    lab.run(argc, argv);

    return 0;
}
