#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CFEATUREDETECTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CFEATUREDETECTAPP_H_

#include <app/interface/IApplication.h>

class CFeatureDetectApp: public IApplication
{
public:
    CFeatureDetectApp();
    virtual ~CFeatureDetectApp();
    int run(int argc, char const *argv[]);
};

#endif