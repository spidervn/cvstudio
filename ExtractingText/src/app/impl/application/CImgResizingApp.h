#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CIMGRESIZINGAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CIMGRESIZINGAPP_H_

#include <app/interface/IApplication.h>

class CImgResizingApp: public IApplication
{
public:
    CImgResizingApp();
    virtual ~CImgResizingApp();
    int run(int argc, char const *argv[]);
};

#endif