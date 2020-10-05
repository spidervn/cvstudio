#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CITIZENID_CCITIZENIDAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CITIZENID_CCITIZENIDAPP_H_

#include "app/interface/IApplication.h"
#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <string>
#define CCitizenIDAppPtrNew std::make_shared<CCitizenIDApp>

class CCitizenIDApp: public IApplication
{
public:
    CCitizenIDApp();
    virtual ~CCitizenIDApp();
    
    int run(int argc, char const* argv[]);

protected:
    int calc_low_frequency_image(cv::Mat inp, cv::Mat& out, int ksize);
    double mean_a_subrange(cv::Mat inp, int y, int x, int ksize);
    double convolve_element(cv::Mat inp, cv::Mat kernel, int y, int x, int kcenterx=-1, int kcentery=-1);
    
    int liveness_check();
    int hamming_distance(cv::Mat img1, cv::Mat img2);

    static bool MyDetector(cv::InputArray image, cv::OutputArray faces, cv::CascadeClassifier *face_cascade);
};

#endif