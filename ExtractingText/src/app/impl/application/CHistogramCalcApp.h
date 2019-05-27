#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHISTOGRAMCALCAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHISTOGRAMCALCAPP_H_

#include <app/interface/IApplication.h>

class CHistogramCalcApp: public IApplication
{
public:
    CHistogramCalcApp();
    virtual ~CHistogramCalcApp();
    int run(int argc, char const *argv[]);
};

#endif