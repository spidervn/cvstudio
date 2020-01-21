#ifndef VISIONFUND_VISIONLAB_INTERFACE_IPAINTBOX_H_
#define VISIONFUND_VISIONLAB_INTERFACE_IPAINTBOX_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>

#define PLOT_TYPE_POINT 1
#define PLOT_TYPE_LINE  2

class IPaintbox
{
public:
    virtual ~IPaintbox() {}
    virtual int paintBoard(cv::Mat img, cv::Rect rc) = 0;

    // virtual int plot_function(cv::Mat img, cv::Rect rc, int n, std::vector<double> x, std::vector<double> y, int plot_type) = 0;
};

typedef std::shared_ptr<IPaintbox> IPaintboxPtr;

#endif