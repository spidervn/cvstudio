#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CCNNAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CCNNAPP_H_

#include "app/interface/IApplication.h"

class CCNNApp: public IApplication
{
private:
    /* data */
public:
    CCNNApp(/* args */);
    ~CCNNApp();
    int run(int argc, char const *argv[]);
};

#endif