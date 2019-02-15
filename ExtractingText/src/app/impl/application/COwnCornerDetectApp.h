#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_COWNCORNERDETECTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_COWNCORNERDETECTAPP_H_

#include <app/interface/IApplication.h>

class COwnCornerDetectApp: public IApplication
{
private:
    /* data */
public:
    COwnCornerDetectApp(/* args */);
    ~COwnCornerDetectApp();
    int run(int argc, char const *argv[]);
};

#endif 