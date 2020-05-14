#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHOUGHLINEAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHOUGHLINEAPP_H_

#include <app/interface/IApplication.h>
#include <memory>

#define CHoughLineAppPtrNew std::make_shared<CHoughLineApp>

class CHoughLineApp: public IApplication
{
public:
    CHoughLineApp();
    virtual ~CHoughLineApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_