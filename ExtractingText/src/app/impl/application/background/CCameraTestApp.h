#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CCAMERATESTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CCAMERATESTAPP_H_

#include "app/interface/IApplication.h"

class CCameraTestApp: public IApplication
{
public:
    CCameraTestApp();
    virtual ~CCameraTestApp();
    
    int run(int argc, char const* argv[]);

    int test_transformation();
};

#endif