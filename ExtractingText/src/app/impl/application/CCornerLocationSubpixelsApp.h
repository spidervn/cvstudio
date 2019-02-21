#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCORNERLOCATIONSUBPIXELSAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCORNERLOCATIONSUBPIXELSAPP_H_

#include <vector>
#include <app/interface/IApplication.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CCornerLocationSubpixelsApp: public IApplication
{
private:
    /* data */
    cv::Mat src, src_gray;
    int maxCorners;
    int maxTrackbar;
    cv::RNG rng;

public:
    CCornerLocationSubpixelsApp(/* args */);
    virtual ~CCornerLocationSubpixelsApp();
    int run(int argc, char const *argv[]);

    void fncFeaturesToTrack(int, void*);
    static void OnTrackbarCallback(int,void*);

};

#endif