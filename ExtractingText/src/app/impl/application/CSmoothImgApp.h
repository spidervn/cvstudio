#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSMOOTHIMGAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSMOOTHIMGAPP_H_

#include "app/interface/IApplication.h"

class CSmoothImgApp: public IApplication
{
public:
    CSmoothImgApp();
    ~CSmoothImgApp();

    int run(int argc, char const *argv[]);
    
};

#endif