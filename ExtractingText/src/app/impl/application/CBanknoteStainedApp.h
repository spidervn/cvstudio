#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CBANKNOTESTAINEDAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CBANKNOTESTAINEDAPP_H_

#include <app/interface/IApplication.h>

class CBanknoteStainedApp: public IApplication
{
public:
    CBanknoteStainedApp();
    virtual ~CBanknoteStainedApp();
    int run(int argc, char const *argv[]);
};

#endif 