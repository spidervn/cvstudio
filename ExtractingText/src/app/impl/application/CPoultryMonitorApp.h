#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CPOULTRYMONITORAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CPOULTRYMONITORAPP_H_

#include <app/interface/IApplication.h>


class CPoultryMonitorApp: public IApplication
{
public:
    CPoultryMonitorApp();
    virtual ~CPoultryMonitorApp();
    
    int run(int argc, char const *argv[]);
    int run_watershed(const char* szFile);
    int run_paper(const char* szFile);
};

#endif