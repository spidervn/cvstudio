#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CFACEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CFACEAPP_H_

#include "app/interface/IApplication.h"

class CFaceApp: public IApplication
{
public:
    CFaceApp();
    virtual ~CFaceApp();

    int run(int argc, char const* argv[]);
    
};

#endif