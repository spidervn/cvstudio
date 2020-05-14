#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CITIZENID_CCITIZENIDAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_CITIZENID_CCITIZENIDAPP_H_

#include "app/interface/IApplication.h"
#include <memory>

#define CExtractTextV1PtrNew std::make_shared<CExtractTextV1>

class CExtractTextV1: public IApplication
{
public:
    CExtractTextV1();
    virtual ~CExtractTextV1();

    int run(int argc, char const* argv[]);
    
};

#endif