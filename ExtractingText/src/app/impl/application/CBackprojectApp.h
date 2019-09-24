#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CBACKPROJECTAPP_H__H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CBACKPROJECTAPP_H__H_

#include <app/interface/IApplication.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

class CBackprojectApp: public IApplication
{
private:
    /* data */
public:
    CBackprojectApp(/* args */);
    virtual ~CBackprojectApp();
    int run(int argc, char const *argv[]);

    static void OnChangeTrackbar(int,void*);

public:
    cv::Mat hue;
    cv::Mat src;
    cv::Mat hsv;
    int bins;
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_