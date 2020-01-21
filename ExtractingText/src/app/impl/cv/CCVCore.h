#ifndef EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_
#define EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_

// #include <app/interface/IApplication.h>
#include <app/interface/cv/ICVCore.h>
#include <vector>

typedef std::vector<double> VECTOR;
#define CCVCorePtrNew std::make_shared<CCVCore>()

class CCVCore : public ICVCore
{
public:
    CCVCore();
    ~CCVCore();

    int dodge(cv::Mat img, cv::Mat img2, cv::Mat& res);

    int averageChange_ShiftingWindow(cv::Mat img,
                                                int window_x,
                                                int window_y,
                                                int window_w,
                                                int window_h,
                                                double& E);
    int HarrisCorner(cv::Mat& img);
    int multiplyKernel(cv::Mat img, 
                                    cv::Mat& dst,
                                    Matrix<double>* kernel,
                                    int anchor_x = -1,
                                    int anchor_y = -1);

    int distanceTransform(cv::Mat img, cv::Mat& dst);
    int distanceTransform_Rotate(cv::Mat img, cv::Mat& dst);
    int contourRect(const std::vector<cv::Point>& v, cv::Rect& r);

    int sobel(cv::Mat img, cv::Mat&dst);
    int gaussianPyramid(cv::Mat img, cv::Mat& dst);
    int gaussianPyramidUp(cv::Mat img, cv::Mat& dst);

    int canny(cv::Mat img, cv::Mat& dst);
    int bucketingColor(cv::Mat img, int range, cv::Mat& dst);

    int nextRNG();
    int lehmerRNG(int p, int n, int seed, std::vector<int>& v);

    int convexHull(std::vector<std::vector<cv::Point>> contours, std::vector<cv::Point>& vhull);
};

#endif // !EXTRACTTEXT_APP_IMPL_CV_CCVCORE_H_