#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCANNYEDGEMANUALAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCANNYEDGEMANUALAPP_H_

#include <app/interface/IApplication.h>

class CCannyEdgeManualApp: public IApplication
{
private:
    /* data */
public:
    CCannyEdgeManualApp(/* args */);
    virtual ~CCannyEdgeManualApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_