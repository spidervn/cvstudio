#ifndef EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CHOUGHLINETEST_H_
#define EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CHOUGHLINETEST_H_

#include "app/interface/IApplication.h"

class CHoughLineTest: public IApplication
{
public:
    CHoughLineTest();
    virtual ~CHoughLineTest();


    int run(int argc, char const* argv[]);
};

#endif