#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CPOULTRYMONITORAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CPOULTRYMONITORAPP_H_

#include <app/interface/IApplication.h>
#include <vector>
#include <opencv2/core.hpp>

class CPoultryMonitorApp: public IApplication
{
public:
    CPoultryMonitorApp();
    virtual ~CPoultryMonitorApp();
    
    int run(int argc, char const *argv[]);
    int run_watershed(const char* szFile);
    int run_paper(const char* szFile);
    int run_video(const char* szFile, const char* szIni);

    int run_extract(const char* szFile);
    int run_contours(const char* szFile, int thresh = 100);
    int run_morph(const char* szFile);

    int run_segmentation2(const char* szFile, const char* szIni);
    int examine_watershed(const char* szFile, const char* szIni);
    int run_video_seg(const char* szFile, const char* szFolderTemp);

    int grouping_flocks(std::vector<cv::Rect> vPoultry, std::vector<int>& vLabel);
};

#endif