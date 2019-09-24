#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CTEMPLATEMATCHING_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CTEMPLATEMATCHING_H_

#include <app/interface/IApplication.h>

class CTemplateMatchingApp: public IApplication
{
public:
    CTemplateMatchingApp();
    virtual ~CTemplateMatchingApp();
    int run(int argc, char const *argv[]);
};

#endif