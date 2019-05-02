#ifndef EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_
#define EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_

// #include <app/interface/IApplication.h>
#include <app/interface/cv/ICVCore.h>
#include <vector>

typedef std::vector<double> VECTOR;

class CCVCore : public ICVCore
{
public:
    CCVCore();
    ~CCVCore();

    int HarrisCorner(cv::Mat& img);
    int multiplyKernel(cv::Mat img, 
                                    cv::Mat& dst,
                                    Matrix<double>* kernel,
                                    int anchor_x = -1,
                                    int anchor_y = -1);

    int distanceTransform(cv::Mat img, cv::Mat& dst);
    int distanceTransform_Rotate(cv::Mat img, cv::Mat& dst);
};

#endif // !EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_