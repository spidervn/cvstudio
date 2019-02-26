#include "CCVCore.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

CCVCore::CCVCore()
{}

CCVCore::~CCVCore()
{}

int CCVCore::HarrisCorner(cv::Mat& img)
{
    /* 
     * Implement
     */
    int nNumChannel = img.channels();
    printf("NoChannels = %d\r\n", nNumChannel);

    if (nNumChannel == 1)
    {
        MatIterator_<uchar> it, end;
        for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; ++it)
        {
        }
    }
    else
    {
        int x = 0;
        int y = 0;
        MatIterator_<Vec3b> it, end;
        int i = 0;
        for ( it = img.begin<Vec3b>(), end = img.end<Vec3b>(); it != end;)
        {
            for (x=0;x<img.cols;x++)
            {                
                ++it;
                
                
            }
            y++;
        }
        printf("done x=%d;y=%d\r\n", x, y);
    }

    // Scan every pixels
    /*
    for (int i=0;i<img.rows;i++)
    {
        for (int j=0;j<img.cols;j++)
        {
            switch (img.channels())
            {
                case 1:
                    {
                        MatIterator_<uchar> it, end;
                        for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; ++it)
                        {
                            *it; // Here
                        }
                    
                    break;
                case 3:
                        MatIterator_<Vec3b> it, end;
                        for ( it = img.begin<Vec3b>(), end = img.end<Vec3b>(); it != end; ++it)
                        {
                        }
                    break;
                default:
                    break;
            }
        }
    }
    */

    return 0;
}

int CCVCore::multiplyKernel(cv::Mat img, Matrix<double>*  kernel, cv::Mat& dst)
{
    // 
    // 
    // 
    double* p_Row = kernel->rows();
    return 0;
}