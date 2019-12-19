#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CVIDEOCROPAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CVIDEOCROPAPP_H_

#include "app/interface/IApplication.h"

class CVideoCropApp: public IApplication
{
private:
    /* data */
public:
    CVideoCropApp(/* args */);
    ~CVideoCropApp();

    int run(int, char const* argv[]);
};

#endif