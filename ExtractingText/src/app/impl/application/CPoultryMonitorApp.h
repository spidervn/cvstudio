#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CPOULTRYMONITORAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CPOULTRYMONITORAPP_H_

#include <app/interface/IApplication.h>


class CPoultryMonitorApp: public IApplication
{
public:
    CPoultryMonitorApp();
    virtual ~CPoultryMonitorApp();
    int run(int argc, char const *argv[]);
};

#endif