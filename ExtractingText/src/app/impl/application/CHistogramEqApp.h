#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHISTOGRAMEQAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHISTOGRAMEQAPP_H_

#include <app/interface/IApplication.h>

class CHistogramEqApp: public IApplication
{
public:
    CHistogramEqApp();
    virtual ~CHistogramEqApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_