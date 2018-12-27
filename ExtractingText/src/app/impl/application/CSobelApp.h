#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSOBELAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSOBELAPP_H_

#include <app/interface/IApplication.h>

class CSobelApp: public IApplication
{
public:
    CSobelApp();
    virtual ~CSobelApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_