#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CHARRISCORNERAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CHARRISCORNERAPP_H_

#include <app/interface/IApplication.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CHarrisCornerApp: public IApplication
{
public:
    CHarrisCornerApp();
    virtual ~CHarrisCornerApp();
    int run(int argc, char const *argv[]);

private:
    cv::Mat src;
    cv::Mat src_gray;
    
    int thresh; // = 200;
    int max_thresh; // = 255;
    const char* source_window; //= "Source Image";
    const char* corners_window; // = "Corners detected";

    void cornerHarris_demo(int, void*);
    static void onChangeTrack(int, void*);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_