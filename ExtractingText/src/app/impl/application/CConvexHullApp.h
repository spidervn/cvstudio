#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCONVEXHULLAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCONVEXHULLAPP_H_

#include <app/interface/IApplication.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class CConvexHullApp: public IApplication
{
public:
    CConvexHullApp();
    virtual ~CConvexHullApp();
    int run(int argc, char const *argv[]);

    static void OnThresholdCB(int,void*);

    cv::Mat src;
    cv::Mat src_gray;
    cv::RNG rng; // (12345);
    int thresh;


};


#endif