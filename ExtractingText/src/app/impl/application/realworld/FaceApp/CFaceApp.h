#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CFACEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CFACEAPP_H_

#include "app/interface/IApplication.h"
#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#define CFaceAppPtrNew std::make_shared<CFaceApp>

struct Conf 
{
    cv::String model_path;
    double scaleFactor;
    Conf(cv::String s, double d);

    cv::CascadeClassifier face_detector;
};

class CFaceApp: public IApplication
{
public:
    CFaceApp();
    virtual ~CFaceApp();

    int run(int argc, char const* argv[]);
    int ex01(const char* file);
    int ex02(const char* file);
    int ex03(const char* file);

    int ex04(const char* file);

    int eigen_face(const char* file);
    int eigen_vector(const cv::Mat& m, cv::Mat& vec_eigen, double& eigen_value);

    static bool myDetector(cv::InputArray img, cv::OutputArray faces, void* pconf);

private:
    void calcSQI(const char* szFile);
    void lambertianModel();
};

#endif