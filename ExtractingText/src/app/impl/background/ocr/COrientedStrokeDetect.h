#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_OCR_CORIENTEDSTROKEDETECT_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_OCR_CORIENTEDSTROKEDETECT_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class COrientedStrokeDetect
{
private:
    /* data */
public:
    COrientedStrokeDetect(/* args */);
    ~COrientedStrokeDetect();

    cv::Mat F(double a, double b);
    cv::Mat thresholdToZero(cv::Mat inp, double threshold);

    int run(int argc, const char* argv[]);
    void calcResponse(cv::Mat inp, cv::Mat& out);
};

#endif