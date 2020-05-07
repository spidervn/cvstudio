#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSVMNONLINEARAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSVMNONLINEARAPP_H_

#include <app/interface/IApplication.h>
#include <memory>

#define CSVMNonLinearAppPtrNew std::make_shared<CSVMNonLinearApp>()

class CSVMNonLinearApp: public IApplication
{
private:
    /* data */
public:
    CSVMNonLinearApp(/* args */);
    ~CSVMNonLinearApp();
    int run(int argc, char const *argv[]);
    int run2(int argc, char const *argv[]);
};


#endif