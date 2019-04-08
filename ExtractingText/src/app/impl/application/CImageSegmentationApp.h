#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CIMAGESEGMENTATIONAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CIMAGESEGMENTATIONAPP_H_

#include <app/interface/IApplication.h>

class CImageSegmentationApp: public IApplication
{
private:
    /* data */
public:
    CImageSegmentationApp(/* args */);
    ~CImageSegmentationApp();
    int run(int argc, char const *argv[]);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_