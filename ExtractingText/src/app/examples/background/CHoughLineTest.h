#ifndef EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CHOUGHLINETEST_H_
#define EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CHOUGHLINETEST_H_

#include "app/interface/IApplication.h"
#include <memory>
#define CHoughLineTestPtrNew std::make_shared<CHoughLineTest>

class CHoughLineTest: public IApplication
{
public:
    CHoughLineTest();
    virtual ~CHoughLineTest();


    int run(int argc, char const* argv[]);
};

#endif