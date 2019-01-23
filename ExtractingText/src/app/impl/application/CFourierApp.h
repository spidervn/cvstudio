#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CFOURIERAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CFOURIERAPP_H_

#include <app/interface/IApplication.h>

class CFourierApp: public IApplication
{
public:
    CFourierApp();
    virtual ~CFourierApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_