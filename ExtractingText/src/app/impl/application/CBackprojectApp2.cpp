#include "CBackprojectApp2.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <stdlib.h>
using namespace cv;
using namespace std;

CBackprojectApp2::CBackprojectApp2(/* args */)
{
}

CBackprojectApp2::~CBackprojectApp2()
{
}

int CBackprojectApp2::run(int argc, char const *argv[])
{
    printf("calc_backproject <<image_model>> <<test_image>>\r\n");

    Mat src;    
    Mat hsv;
    Mat hue;
    Mat hist;
    Mat imgTest;
    Mat imgTHsv;
    Mat imgTHue;
    Mat bprj;

    int bins = 25;
    int ch[] = { 0, 0};
    int histSize = MAX(bins, 2);
    float hue_range[] = { 0, 180};
    const float* ranges = { hue_range };
    const char* szWin = "Window";
    
    src = imread(argv[1]);
    imgTest = imread(argv[2]);

    cvtColor(src, hsv, COLOR_BGR2HSV);
    cvtColor(imgTest, imgTHsv, COLOR_BGR2HSV);

    hue.create(hsv.size(), hsv.depth());
    imgTHue.create(imgTHsv.size(), imgTHsv.depth());

    mixChannels( &hsv, 1, &hue, 1, ch, 1);
    mixChannels( &imgTHsv, 1, &imgTHue, 1, ch, 1);

    // namedWindow(szWin);

    calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat())    ;

    calcBackProject(&imgTHue, 1, 0, hist, bprj, &ranges, 1, true);

    imshow("src-hue", hsv);
    imshow("test-img", imgTHsv);
    imshow("BackProject", bprj);
    waitKey();
    return 0;
}