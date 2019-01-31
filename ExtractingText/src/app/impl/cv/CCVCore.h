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
};

#endif // !EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_