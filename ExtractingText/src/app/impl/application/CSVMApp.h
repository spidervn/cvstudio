#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSVMAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSVMAPP_H_

#include <app/interface/IApplication.h>

class CSVMApp: public IApplication
{
public:
    CSVMApp();
    virtual ~CSVMApp();
    int run(int argc, char const *argv[]);
    int run2();
    int run3();
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_