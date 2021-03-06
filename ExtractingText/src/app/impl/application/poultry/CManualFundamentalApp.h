#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CMANUALFUNDAMENTALAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CMANUALFUNDAMENTALAPP_H_

#include "app/interface/IApplication.h"
#include <memory>

#define CManualFundamentalAppPtrNew std::make_shared<CManualFundamentalApp>

class CManualFundamentalApp: public IApplication
{
private:
    /* data */
public:
    CManualFundamentalApp(/* args */);
    ~CManualFundamentalApp();

    int run(int argc, char const *argv[]);

};

#endif