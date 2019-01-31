#ifndef EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_
#define EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_

#include <opencv2/core.hpp>

class ICVCore
{
public:
    ~ICVCore() { }
    virtual int HarrisCorner(cv::Mat& img) = 0;
};

#endif // !EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_