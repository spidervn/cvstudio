#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_CALCULUS_ICALCULUSGENERAL_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_CALCULUS_ICALCULUSGENERAL_H_

#include <opencv2/core.hpp>

class ICalculusGeneral
{
public:
    virtual ~ICalculusGeneral() {}
    virtual int rotation2D_CW(double alpha, cv::Mat& rot_Matrix) = 0;  // Counter Clockwise
};

#endif