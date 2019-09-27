#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CCONTRASTAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CCONTRASTAPP_H_

#include <app/interface/IApplication.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class CContrastApp: public IApplication
{
public:
    CContrastApp();
    virtual ~CContrastApp();
    int run(int argc, char const *argv[]);
};

#endif