#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CEXTRACTTEXTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CEXTRACTTEXTAPP_H_

#include <app/interface/IApplication.h>

class CExtractTextApp: public IApplication
{
private:
    /* data */
public:
    CExtractTextApp(/* args */);
    virtual ~CExtractTextApp();
    int run(int argc, char const *argv[]);
};



#endif // !\