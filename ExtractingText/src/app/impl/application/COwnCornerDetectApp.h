#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_COWNCORNERDETECTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_COWNCORNERDETECTAPP_H_

#include <app/interface/IApplication.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class COwnCornerDetectApp: public IApplication
{
private:
    /* data */
    cv::Mat src;
    cv::Mat src_gray;
    cv::Mat myHarris_dst;
    cv::Mat myHarris_cpy;
    cv::Mat Mc;
    cv::Mat myShiTomasi_dst;
    cv::Mat myShiTomasi_cpy;

    cv::RNG rng;

    double myHarris_minVal;
    double myHarris_maxVal;
    double myShiTomasi_minVal;
    double myShiTomasi_maxVal;

    int myShiTomasi_qualityLevel;
    int myHarris_qualityLevel;
    int max_qualityLevel;

public:
    COwnCornerDetectApp(/* args */);
    ~COwnCornerDetectApp();
    int run(int argc, char const *argv[]);

    int myHarrisFunc(int, void*);
    int myShiTomasiFunc(int, void*);

    static void OnTrackbarHarris(int,void*);
    static void OnTrackbarShiTomasi(int,void*);
};

#endif 