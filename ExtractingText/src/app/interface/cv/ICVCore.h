#ifndef EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_
#define EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_

#include <opencv2/core.hpp>
#include "app/interface/background/IMatrix.h"
#include <memory>
#include <vector>

class ICVCore
{
public:
    ~ICVCore() { }

    virtual int dodge(cv::Mat img, cv::Mat img2, cv::Mat& res) = 0;

    virtual int HarrisCorner(cv::Mat& img) = 0;

    virtual int averageChange_ShiftingWindow(cv::Mat img,
                                                int window_x,
                                                int window_y,
                                                int window_w,
                                                int window_h,
                                                double& E) = 0;
    virtual int multiplyKernel(cv::Mat img, 
                                    cv::Mat& dst,
                                    Matrix<double>* kernel,
                                    int anchor_x = -1,
                                    int anchor_y = -1) = 0;

    virtual int distanceTransform(cv::Mat img, cv::Mat& dst) = 0;

    virtual int contourRect(const std::vector<cv::Point>& v, cv::Rect& r) = 0;

    virtual int sobel(cv::Mat img, cv::Mat&dst) = 0;

    virtual int gaussianPyramid(cv::Mat img, cv::Mat& dst) = 0;

    virtual int gaussianPyramidUp(cv::Mat img, cv::Mat& dst) = 0;

    virtual int canny(cv::Mat img, cv::Mat& dst) = 0;

    virtual int bucketingColor(cv::Mat img, int range, cv::Mat& dst) = 0;

    virtual int nextRNG() = 0;

    virtual int lehmerRNG(int p, int n, int seed, std::vector<int>& v) = 0;

    virtual int convexHull(std::vector<std::vector<cv::Point>> contours, std::vector<cv::Point>& vhull) = 0;
};

typedef std::shared_ptr<ICVCore> ICVCorePtr;

#endif // !EXTRACTTEXT_APP_INTERFACE_CV_ICVCORE_H_