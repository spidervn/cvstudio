#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CITIZENID_CCITIZENIDAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CITIZENID_CCITIZENIDAPP_H_

#include "app/interface/IApplication.h"

class CCitizenIDApp: public IApplication
{
public:
    CCitizenIDApp();
    virtual ~CCitizenIDApp();
    
    int run(int argc, char const* argv[]);
};

#endif