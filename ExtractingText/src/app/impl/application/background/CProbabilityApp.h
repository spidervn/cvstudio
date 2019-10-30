#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CPROBABILITYAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CPROBABILITYAPP_H_

#include <app/interface/IApplication.h>

class CProbabilityApp: public IApplication
{
private:
    /* data */
public:
    CProbabilityApp(/* args */);
    virtual ~CProbabilityApp();
    int run(int argc, char const *argv[]);
};

#endif