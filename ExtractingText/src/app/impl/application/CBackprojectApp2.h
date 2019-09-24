#ifndef EXTRACTINGTEXT_APP_IMPL_APPLICATIONL_CBACKPROJECTAPP2_H_
#define EXTRACTINGTEXT_APP_IMPL_APPLICATIONL_CBACKPROJECTAPP2_H_

#include <app/interface/IApplication.h>

class CBackprojectApp2: public IApplication
{
private:
    /* data */
public:
    CBackprojectApp2(/* args */);
    virtual ~CBackprojectApp2();
    int run(int argc, char const *argv[]);
};

#endif
