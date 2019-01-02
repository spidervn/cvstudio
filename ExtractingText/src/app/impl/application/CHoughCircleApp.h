#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHOUGHCIRCLE_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHOUGHCIRCLE_H_

#include <app/interface/IApplication.h>

class CHoughCircleApp: public IApplication
{
public:
    CHoughCircleApp();
    virtual ~CHoughCircleApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_