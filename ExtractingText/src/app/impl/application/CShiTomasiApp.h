#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSHITOMASIAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSHITOMASIAPP_H_

#include <app/interface/IApplication.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

class CShiTomasiApp : public IApplication
{
private:
    /* data */
public:
    CShiTomasiApp(/* args */);
    virtual ~CShiTomasiApp();
    int run(int argc, char const *argv[]);

    void goodFeaturesToTrack_Demo( int, void* );
    static void TrackbarCallback( int, void* );
protected:
    cv::Mat src, src_gray;
    int maxCorners;
    int maxTrackbar;
    cv::RNG rng;
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_