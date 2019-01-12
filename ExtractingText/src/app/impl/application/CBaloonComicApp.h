#ifndef EXTRACTINGTEXT_APP_IMPL_APPLICATIONL_CBALOONCOMICAPP_H_
#define EXTRACTINGTEXT_APP_IMPL_APPLICATIONL_CBALOONCOMICAPP_H_

#include <app/interface/IApplication.h>

class CBaloonComicApp : public IApplication
{
public:
    CBaloonComicApp();
    virtual ~CBaloonComicApp();
    int run(int argc, char const *argv[]);
};

#endif
