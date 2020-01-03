#ifndef VISIONFUND_VISIONLAB_INTERFACE_IPAINTBOX_H_
#define VISIONFUND_VISIONLAB_INTERFACE_IPAINTBOX_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>

class IPaintbox
{
public:
    virtual ~IPaintbox() {}
    virtual int paintBoard(cv::Mat img, cv::Rect rc) = 0;
};

typedef std::shared_ptr<IPaintbox> IPaintboxPtr;

#endif