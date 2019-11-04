#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CALCULUS_CCALCULUSAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CALCULUS_CCALCULUSAPP_H_

#include <app/interface/IApplication.h>

class CCalculusApp: public IApplication
{
private:
    /* data */
public:
    CCalculusApp(/* args */);
    ~CCalculusApp();
    int run(int, char const *[]);
};

#endif