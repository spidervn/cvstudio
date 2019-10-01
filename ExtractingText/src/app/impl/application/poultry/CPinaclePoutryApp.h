#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CPINACLEPOULTRYAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CPINACLEPOULTRYAPP_H_

#include <app/interface/IApplication.h>

class CPinaclePoutryApp: public IApplication
{
private:
    /* data */
public:
    CPinaclePoutryApp(/* args */);
    ~CPinaclePoutryApp();
    int run(int argc, char const *argv[]);

    int mergeTwoFrame();
};

#endif 