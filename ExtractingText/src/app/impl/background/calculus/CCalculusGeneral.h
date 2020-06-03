#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_CALCULUS_CCALCULUSGENERAL_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_CALCULUS_CCALCULUSGENERAL_H_

#include <app/interface/background/calculus/ICalculusGeneral.h>

class CCalculusGeneral: public ICalculusGeneral
{
public:
    CCalculusGeneral();
    virtual ~CCalculusGeneral();
    
    int rotation2D_CW(double alpha, cv::Mat& rot_Matrix);  // Counter Clockwise
};

#endif