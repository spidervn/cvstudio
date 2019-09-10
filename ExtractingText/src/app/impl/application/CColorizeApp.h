#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCOLORIZEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCOLORIZEAPP_H_

#include <app/interface/IApplication.h>

class CColorizeApp: public IApplication
{
public:
    CColorizeApp();
    virtual ~CColorizeApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_