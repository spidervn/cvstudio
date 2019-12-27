#ifndef VISIONFUND_INTERFACE_IIMGPROCESS_H_
#define VISIONFUND_INTERFACE_IIMGPROCESS_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <memory>

class IImgProcess
{
private:
    /* data */
public:
    virtual ~IImgProcess() {}
    virtual int derivative(cv::Mat img, cv::Mat& dest) = 0;
};

typedef std::shared_ptr<IImgProcess> IImgProcessPtr;

#endif