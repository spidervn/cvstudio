#ifndef EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_
#define EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_

#include <opencv2/core.hpp>
#include "interface/background/IMatrix.h"

class ICVCore
{
public:
    ~ICVCore() { }

    virtual int HarrisCorner(cv::Mat& img) = 0;
    virtual int multiplyKernel(cv::Mat img, 
                                    cv::Mat& dst,
                                    Matrix<double>* kernel,
                                    int anchor_x = -1,
                                    int anchor_y = -1) = 0;

};

#endif // !EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_