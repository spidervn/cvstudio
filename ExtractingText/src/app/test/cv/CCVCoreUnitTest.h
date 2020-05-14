#ifndef EXTRACTTEXT_APP_TEST_CV_CCVCOREUNITTEST_H_
#define EXTRACTTEXT_APP_TEST_CV_CCVCOREUNITTEST_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class CCVCoreUnitTest
{
public:
    CCVCoreUnitTest();
    virtual ~CCVCoreUnitTest();

    int checkValid_gaussianKernel(const cv::Mat m);
    
};

#endif