#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CAMERA_CCAMERATECHAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CAMERA_CCAMERATECHAPP_H_

#include "app/interface/IApplication.h"
#include <memory>

struct PinholeCoefficient
{
    double k1;
    double k2;

    double p1;
    double p2;

    double k3;
};

#define CCameraTechAppPtrNew std::make_shared<CCameraTechApp>

class CCameraTechApp: public IApplication
{
public:
    CCameraTechApp();
    virtual ~CCameraTechApp();
    
    int run(int argc, char const* argv[]);
};

#endif