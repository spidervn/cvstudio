#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHITORMISSAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHITORMISSAPP_H_

#include <app/interface/IApplication.h>

class CHitOrMissApp: public IApplication
{
public:
    CHitOrMissApp();
    virtual ~CHitOrMissApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_