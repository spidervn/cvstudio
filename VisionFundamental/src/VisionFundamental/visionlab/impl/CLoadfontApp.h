#ifndef VSIONFUND_VISIONLAB_IMPL_CLOADFONTAPP_H_
#define VSIONFUND_VISIONLAB_IMPL_CLOADFONTAPP_H_

#include "visionlab/interface/IApplication.h"

class CLoadfontApp: public IApplication
{
private:
    /* data */
public:
    CLoadfontApp(/* args */);
    virtual ~CLoadfontApp();
    int run(int argc, char const* argv[]);
};


#endif