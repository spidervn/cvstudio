#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CPENCILINGAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CPENCILINGAPP_H_

#include <app/interface/IApplication.h>
#include <opencv2/core.hpp>

class CPencilingApp: public IApplication
{
private:
    /* data */
public:
    CPencilingApp(/* args */);
    ~CPencilingApp();
    int run(int argc, char const *argv[]);


    int change_HSL_toZero(cv::Mat& m, cv::Mat& m1);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_