#ifndef VISIONFUND_INTERFACE_IHISTOGRAM_H_
#define VISIONFUND_INTERFACE_IHISTOGRAM_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class IHistogram
{
private:
    /* data */
public:
    virtual ~IHistogram() {}
    virtual int paintHisgtogram(cv::Mat img, cv::Mat& imgHistogram, int num_bins) = 0;
    
};

#endif 