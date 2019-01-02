#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHOUGHLINEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHOUGHLINEAPP_H_

#include <app/interface/IApplication.h>

class CHoughLineApp: public IApplication
{
public:
    CHoughLineApp();
    virtual ~CHoughLineApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_