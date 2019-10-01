#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCONTOURSAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCONTOURSAPP_H_

#include <app/interface/IApplication.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class CContoursApp: public IApplication
{
public:
    CContoursApp();
    virtual ~CContoursApp();
    int run(int argc, char const *argv[]);

    static void Callback(int,void*);
    void contourRc(const std::vector<cv::Point>& v, cv::Rect& r);

    cv::Mat src;
    cv::Mat src_gray;
    int thresh;
    cv::RNG rng;

};

#endif