#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CAFFINETRANSFORM_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CAFFINETRANSFORM_H_

#include <app/interface/IApplication.h>

class CAffineTransform: public IApplication
{
public:
    CAffineTransform();
    virtual ~CAffineTransform();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_