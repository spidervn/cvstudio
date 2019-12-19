#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CCASCADECLASSIFIERAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CCASCADECLASSIFIERAPP_H_

#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class CCascadeClassifierApp
{
private:
    /* data */
public:
    CCascadeClassifierApp(/* args */);
    ~CCascadeClassifierApp();

private:
    double SAT(cv::Mat m, int x,int y);     // Summed Area Table
    double RSAT(cv::Mat m, int x, int y);   // Rotated summed area table
};

#endif