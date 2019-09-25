#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CANISOTROPICSEGMENTATIONAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CANISOTROPICSEGMENTATIONAPP_H_

#include <app/interface/IApplication.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

class CAnisotropicSegmentation: public IApplication
{
private:
    /* data */
public:
    CAnisotropicSegmentation(/* args */);
    ~CAnisotropicSegmentation();
    int run(int argc, char const *argv[]);
    void calcGST(const cv::Mat& inputImg, cv::Mat& imgCoherencyOut, cv::Mat& imgOrientationOut, int w);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_