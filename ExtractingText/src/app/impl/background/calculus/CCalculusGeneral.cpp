#include "CCalculusGeneral.h"

#include <math.h>
#include <opencv2/core.hpp>


CCalculusGeneral::CCalculusGeneral()
{}

CCalculusGeneral::~CCalculusGeneral()
{}

int CCalculusGeneral::rotation2D_CW(double alpha, cv::Mat& rot_Matrix)  // Counter Clockwise
{
    rot_Matrix = (cv::Mat_<double>(2,2) << cos(alpha), -sin(alpha), sin(alpha), cos(alpha));
    return 0;
}