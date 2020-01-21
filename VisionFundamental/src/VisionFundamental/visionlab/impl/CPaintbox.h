#ifndef VSIONFUND_VISIONLAB_IMPL_CPAINTBOX_H_
#define VSIONFUND_VISIONLAB_IMPL_CPAINTBOX_H_

#include "visionlab/interface/IPaintbox.h"
#include <memory>
#include <vector>

class CPaintbox: public IPaintbox
{
private:
    /* data */
public:
    CPaintbox(/* args */);
    virtual ~CPaintbox();

    int paintBoard(cv::Mat img, cv::Rect rc);
    // int paint_f(int n, std::vector<double> x, std::vector<double> y);
};


#define CPaintboxPtrNew std::make_shared<CPaintbox>()

#endif