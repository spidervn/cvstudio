#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CPYRAMIDMANUALAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CPYRAMIDMANUALAPP_H_

#include <app/interface/IApplication.h>

class CPyramidManualApp: public IApplication
{
public:
    CPyramidManualApp();
    virtual ~CPyramidManualApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_