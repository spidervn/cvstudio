#include "CBackprojectApp.h"
#include <stdlib.h>

using namespace std;
using namespace cv;

CBackprojectApp::CBackprojectApp(/* args */)
{
    bins = 25;
}

CBackprojectApp::~CBackprojectApp()
{
}

int CBackprojectApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: backproject <<image>>\r\n");
        return 0;
    }

    
    int ch[] = { 0, 0};
    const char* szWindow = "Source Window";

    src = imread(argv[1]);
    cvtColor(src, hsv, COLOR_BGR2HSV);

    hue.create(hsv.size(), hsv.depth());

    mixChannels(&hsv, 1, &hue, 1, ch, 1);
    namedWindow(szWindow);

    createTrackbar("* Hue bins: ", szWindow, &bins, 180, OnChangeTrackbar, (void*)this);
    OnChangeTrackbar(0, 0);

    imshow(szWindow, src);
    waitKey();
    return 0;
}

void CBackprojectApp::OnChangeTrackbar(int,void* pData)
{
    if (pData != NULL)
    {
        CBackprojectApp* p_App = (CBackprojectApp*)pData;

        int histSize = MAX(p_App->bins, 2);
        float hue_range[] = { 0, 180 };
        const float* ranges = { hue_range };

        Mat hist;
        calcHist(&p_App->hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
        normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

        Mat backproj;
        calcBackProject(&p_App->hue, 1, 0, hist, backproj, &ranges, 1, true);

        imshow("BackProj",backproj);
        int w = 400;
        int h = 400;
        int bin_w = cvRound((double) w / histSize);
        Mat histImg = Mat::zeros(h, w, CV_8UC3);

        for (int i=0; i < p_App->bins; ++i)
        {
            rectangle(histImg, Point(i*bin_w, h), Point( (i+1)*bin_w, h - cvRound(hist.at<float>(i)*h/255.0)),
            Scalar(0,0,255), FILLED);
        }

        imshow("Histogram", histImg);
    }
    return;
}