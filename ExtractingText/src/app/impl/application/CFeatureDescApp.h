#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CFEATUREDESCAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CFEATUREDESCAPP_H_

#include <app/interface/IApplication.h>

class CFeatureDescApp: public IApplication
{
private:
    /* data */
public:
    CFeatureDescApp(/* args */);
    virtual ~CFeatureDescApp();
    int run(int argc, char const *argv[]);
};

#endif