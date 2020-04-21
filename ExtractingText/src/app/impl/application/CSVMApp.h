#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_CSVMAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_CSVMAPP_H_

#include <app/interface/IApplication.h>
#include <vector>
#include <opencv2/core.hpp>

class CSVMApp: public IApplication
{
public:
    CSVMApp();
    virtual ~CSVMApp();
    int run(int argc, char const *argv[]);
    int run2();
    int run3();
    int run4();


protected:
    int extract_every_characters(const char* szImgFile);
    int homogeneous_geometry();

    int vertically_extract(const char* szFolderIn, const char* szFolderOut);
    int vertically_extract_a_file(const char* szFile, const char* prefix, const char* szFolderOut);

    int find_continuous_zero(
        const cv::Mat& sumVector,   // n x 1 matrix 
        std::vector<cv::Vec2i>& res, // Array of Vec2i(startlocation, endlocation) 
        int min_continous_len = 3
    );

    int find_continuous_nonzero(
        const cv::Mat& sumVector,   // n x 1 matrix 
        std::vector<cv::Vec2i>& res, // Array of Vec2i(startlocation, endlocation) 
        int min_continous_len = 3
    );
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_