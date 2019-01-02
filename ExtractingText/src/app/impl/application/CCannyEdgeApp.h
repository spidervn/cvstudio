#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCANNYEDGE_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCANNYEDGE_H_

#include <app/interface/IApplication.h>

class CCannyEdgeApp: public IApplication
{
public:
    CCannyEdgeApp();
    virtual ~CCannyEdgeApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_