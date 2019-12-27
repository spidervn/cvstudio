#ifndef VISIONFUND_IMPL_CIMGPROCESS_H_
#define VISIONFUND_IMPL_CIMGPROCESS_H_

#include <memory>
#include "visionfund/interface/IImgProcess.h"

class CImgProcess: public IImgProcess
{
private:
    /* data */
public:
    CImgProcess(/* args */);
    ~CImgProcess();

    int derivative(cv::Mat img, cv::Mat& dest);
};

#define CImgProcessPtrNew std::make_shared<CImgProcess>()

#endif