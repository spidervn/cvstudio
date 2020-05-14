#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CFACEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CFACEAPP_H_

#include "app/interface/IApplication.h"
#include <memory>

#define CFaceAppPtrNew std::make_shared<CFaceApp>

class CFaceApp: public IApplication
{
public:
    CFaceApp();
    virtual ~CFaceApp();

    int run(int argc, char const* argv[]);
    int ex01(const char* file);
    int ex02(const char* file);
    
};

#endif