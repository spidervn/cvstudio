#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CHELENPARSER_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_REALWORLD_FACEAPP_CHELENPARSER_H_

#include "app/interface/IApplication.h"
#include <memory>

#define CHelenParserPtrNew std::make_shared<CHelenParser>

class CHelenParser: public IApplication
{
public:
    CHelenParser();
    virtual ~CHelenParser();
    int run(int argc, char const* argv[]);
};

#endif