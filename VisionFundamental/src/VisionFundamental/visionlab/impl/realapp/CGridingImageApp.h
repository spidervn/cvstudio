#ifndef VSIONFUND_VISIONLAB_IMPL_REALAPP_CGRIDINGIMAGEAPP_H_
#define VSIONFUND_VISIONLAB_IMPL_REALAPP_CGRIDINGIMAGEAPP_H_

#include "visionlab/interface/IApplication.h"

class CGridingImageApp: public IApplication
{
private:
    /* data */
public:
    CGridingImageApp(/* args */);
    ~CGridingImageApp();

    virtual int run(int argc, char const* argv[]);

};

#endif