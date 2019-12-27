#include "CImgProcess.h"
#include <opencv2/core.hpp>

using namespace cv;

CImgProcess::CImgProcess(/* args */)
{}

CImgProcess::~CImgProcess()
{}

int CImgProcess::derivative(cv::Mat img, cv::Mat& dest)
{
    if (img.channels() == 1)
    {
        dest.create(cv::Size(img.cols-1, img.rows - 1), CV_8UC1);

        for( int i = 0; i < img.rows-1; ++i)
        {
            for( int j = 0; j < img.cols-1; ++j )
            {
                dest.at<uchar>(i,j) = sqrt((img.at<uchar>(i+1,j) - img.at<uchar>(i,j)) * 
                                            ( img.at<uchar>(i,j+1) - img.at<uchar>(i,j)));
            }
        }

        // normalize(dest, dest, 0, 255, NORM_MINMAX);
    }
    else if (img.channels() == 3)
    {
        dest.create(cv::Size(img.cols -1, img.rows -1), CV_8UC3);
        
        Mat_<Vec3s> _dest = dest;
        Mat_<Vec3b> _img = img;

        for( int i = 0; i < img.rows-1; ++i)
        {
            for( int j = 0; j < img.cols-1; ++j )
            {
                _dest(i,j)[0] = (_img(i+1,j)[0] - _img(i,j)[0]) * (_img(i,j+1)[0] - _img(i,j+1)[0]);
                _dest(i,j)[1] = (_img(i+1,j)[1] - _img(i,j)[1]) * (_img(i,j+1)[1] - _img(i,j+1)[1]);
                _dest(i,j)[2] = (_img(i+1,j)[2] - _img(i,j)[2]) * (_img(i,j+1)[2] - _img(i,j+1)[2]);
            }
        }

        // normalize(dest, dest, 0, 255, NORM_MINMAX);
    }

    return 0;
}


