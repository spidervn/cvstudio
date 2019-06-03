#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSOBELMANUALAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSOBELMANUALAPP_H_

#include <app/interface/IApplication.h>

class CSobelManualApp: public IApplication
{
public:
    CSobelManualApp();
    virtual ~CSobelManualApp();
    int run(int argc, char const *argv[]);
};

#endif 