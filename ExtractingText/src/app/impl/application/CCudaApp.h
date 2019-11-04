
#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CEXTRACTTEXTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CEXTRACTTEXTAPP_H_

#include <app/interface/IApplication.h>

class CCudaApp: public IApplication
{
private:
    /* data */
public:
    CCudaApp(/* args */);
    ~CCudaApp();
    int run(int,char const *[]);
};

#endif