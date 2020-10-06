#include "CDeskewLab.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

CDeskewLab::CDeskewLab(/* args */)
{
}

CDeskewLab::~CDeskewLab()
{
}

int CDeskewLab::run(int argc, char const* argv[])
{
    return 0;
}

int CDeskewLab::skewangle_est(const char* file)
{
    cv::Mat img = imread(file, IMREAD_GRAYSCALE);
    cv::Mat bw;
    cv::Scalar mean = cv::mean(img);

    int imean =  (int)mean[0];
    cv::threshold(img, bw, imean, 255, CV_THRESH_BINARY);

    

    return 0;
}

