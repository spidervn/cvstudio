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
    int run4();


    int extract_every_characters(const char* szImgFile);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_