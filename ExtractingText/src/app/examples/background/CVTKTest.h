#ifndef EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CVTKTEST_H_
#define EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CVTKTEST_H_

#include <memory>
#include "app/interface/IApplication.h"

#define CVTKTestPtrNew std::make_shared<CVTKTest>()

class CVTKTest: public IApplication
{
public:
    CVTKTest();
    virtual ~CVTKTest();
    
    int run(int argc, char const* argv[]);
    int run1();
    int run2();
};

#endif