#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CLAPLACEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CLAPLACEAPP_H_

#include <app/interface/IApplication.h>

class CLaplaceApp: public IApplication
{
public:
    CLaplaceApp() {}
    virtual ~CLaplaceApp() {}
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_