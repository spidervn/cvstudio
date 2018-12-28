#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CREMAPPINGAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CREMAPPINGAPP_H_

#include <app/interface/IApplication.h>

class CRemappingApp: public IApplication
{
public:
    CRemappingApp();
    virtual ~CRemappingApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_