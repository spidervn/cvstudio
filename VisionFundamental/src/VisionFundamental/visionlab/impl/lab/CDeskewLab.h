#ifndef VSIONFUND_VISIONLAB_IMPL_LAB_CDESKEWLAB_H_
#define VSIONFUND_VISIONLAB_IMPL_LAB_CDESKEWLAB_H_

#include "visionlab/interface/IApplication.h"

class CDeskewLab: public IApplication
{
private:
    /* data */
public:
    CDeskewLab(/* args */);
    virtual ~CDeskewLab();

    int run(int argc, char const* argv[]);

    int skewangle_est(const char* file);
};

#endif