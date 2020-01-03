#ifndef VSIONFUND_VISIONLAB_IMPL_CPAINTBOX_H_
#define VSIONFUND_VISIONLAB_IMPL_CPAINTBOX_H_

#include "visionlab/interface/IPaintbox.h"
#include <memory>

class CPaintbox: public IPaintbox
{
private:
    /* data */
public:
    CPaintbox(/* args */);
    virtual ~CPaintbox();

    int paintBoard(cv::Mat img, cv::Rect rc);
};


#define CPaintboxPtrNew std::make_shared<CPaintbox>()

#endif