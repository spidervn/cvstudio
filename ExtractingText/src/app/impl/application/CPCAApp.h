#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CPCAAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CPCAAPP_H_

#include <app/interface/IApplication.h>
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>

#define CPCAAppPtrNew std::make_shared<CPCAApp>

class CPCAApp: public IApplication
{
public:
    CPCAApp();
    virtual ~CPCAApp();
    int run(int argc, char const *argv[]);

    double getOrientation(const std::vector<cv::Point> &pts, cv::Mat &img);
    void drawAxis(cv::Mat& img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale = 0.2);

};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_