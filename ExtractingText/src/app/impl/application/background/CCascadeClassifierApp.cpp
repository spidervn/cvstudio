#include "CCascadeClassifierApp.h"

CCascadeClassifierApp::CCascadeClassifierApp(/* args */)
{
}

CCascadeClassifierApp::~CCascadeClassifierApp()
{
}

double CCascadeClassifierApp::SAT(cv::Mat m, int x,int y)
{
    double sat = 0.0;

    if (m.channels() == 1)
    {
        for (int y1=0; y1<=y; y1++)
        {
            for (int x1=0;x1<=x; ++x1)
            {
                sat += m.at<uchar>(y1,x1);
            }
        }
    }

    return 0.0;
}

double CCascadeClassifierApp::RSAT(cv::Mat m, int x, int y)   // Rotated summed area table
{
    return 0.0;
}