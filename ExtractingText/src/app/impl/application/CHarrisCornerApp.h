#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHARRISCORNERAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHARRISCORNERAPP_H_

#include <app/interface/IApplication.h>

class CHarrisCornerApp: public IApplication
{
public:
    CHarrisCornerApp();
    virtual ~CHarrisCornerApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_