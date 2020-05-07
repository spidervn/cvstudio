#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CHOUGHTRANSFORMAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_BACKGROUND_CHOUGHTRANSFORMAPP_H_

#include "app/interface/IApplication.h"
#include <memory>

#define CHoughTransformAppPtrNew std::make_shared<CHoughTransformApp>()

class CHoughTransformApp: public IApplication
{
public:
    CHoughTransformApp();
    virtual ~CHoughTransformApp();
    
    int run(int argc, char const* argv[]);
};

#endif