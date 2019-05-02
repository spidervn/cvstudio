#include "CCVCore.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#define VMALLOC(v, type, element_size) v = (type*)malloc(sizeof(type) * element_size)
#define VFREE(v) free(v)
#define VMALLOC_2D(v, type, row, col) v = (type**)malloc(sizeof(type*) * row); for (int yyyyy000=0;yyyyy000<row;yyyyy000++) { v[yyyyy000] = (type*) malloc(sizeof(type) * col); }
#define VFREE_2D(v, type, row, col) for (int yyyyy000=0;yyyyy000<row;yyyyy000++) { free(v[yyyyy000]); } free(v);

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

int CCVCore::multiplyKernel(cv::Mat img, 
                                    cv::Mat& dst,
                                    Matrix<double>* kernel,
                                    int anchor_x,
                                    int anchor_y)
{
    double* p_Row = kernel->rows(0);

    if (anchor_x == -1)
    {
        anchor_x = kernel->cols() / 2;
    }

    if (anchor_y == -1)
    {
        anchor_y = kernel->rows() / 2;
    }

    /*
    for(size_t i = 0; i < img.rows(); i++)
    {
        for(size_t i = 0; i < count; i++)
        {
            
        }
    }
    */

    // 
    // Window: (u,v).
    // 



    return 0;
}

int CCVCore::distanceTransform(cv::Mat img, cv::Mat& dst)
{
    if (img.channels() == 1)
    {
        // 
        // Calculating 1DF 
        // calculating 1df
        // df(x,y) = min{xp} ((x-xp)^2 + df_{xp}(y))
        //
        // Build a lookup matrix df_{xp}(y)
        // 

        int m = img.rows;
        int n = img.cols;

        // Columns index by 
        double** df;
        double* z;
        int* v;
        double MAX_INFINITE = 9999999;
        // df = (double**) malloc(sizeof(double*) * m * n);
        // z = (double*) malloc(sizeof(double) * ());
        VMALLOC_2D(df, double, m, n);
        VMALLOC(v, int, m+1);
        VMALLOC(z, double, m+1);

        // 
        // Calculate DF for every columns
        //  df[a][column_x] = 
        // 
        for (int x=0; x<n; ++x)
        {
            int k = 0;
            double s;
            v[k] = 0;
            z[k] = 0;
            z[k+1] = MAX_INFINITE;
            
            for (int q = 0; q<m; ++q)
            {
                bool bBreak = false;
                do
                {
                    double f_q = img.at<uchar>(q, x);
                    double f_vk = img.at<uchar>(v[k], x);
                    s = (  f_q * f_q + q*q - f_vk * f_vk - v[k]*v[k])/(2*q - 2*v[k]);

                    if (z[k] <= s)
                    {
                        k = k-1;
                    }
                    else
                    {
                        bBreak = true;
                    }
                }
                while (!bBreak);

                k = k+1;
                v[k] = q;
                z[k] = s;
                z[k+1] = MAX_INFINITE;
            }

            k = 0;
            for (int q = 0; q<m; q++)
            {
                
            }

        }

        // 
        // Calculate Distance-transform for each row
        // 

        for (int x=0; x<n; x++)
        {
            for (int y=0; y<m; ++y)
            {

            }
        }

        // 
        // 
        /*
        for (int y=0; y<m; ++y)
        {
            free(df[y]);
        }
        free(df);
        */
    VFREE_2D(df, double, m, n);
    VFREE(v);
    VFREE(z);
    }
}

int CCVCore::distanceTransform_Rotate(cv::Mat img, cv::Mat& dst)
{
    return 0;
}