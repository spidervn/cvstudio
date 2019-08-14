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

int CCVCore::averageChange_ShiftingWindow(cv::Mat img,
                                                int window_x,
                                                int window_y,
                                                int window_w,
                                                int window_h,
                                                double& E)
{
    return 0;
}                                                

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

        dst = img.clone();

        // Columns index by 
        double** df;
        double** df2;
        double* z;
        int* v;
        double MAX_INFINITE = 9999999;

        printf("HERE\r\n");

        VMALLOC_2D(df, double, m, n);
        VMALLOC_2D(df2, double, m, n);
        VMALLOC(v, int, m+1);
        VMALLOC(z, double, m+1);

        printf("MALLOCDONE\r\n");

        // 
        // Calculate DF for every columns
        // 
        for (int x=0; x<n; ++x)
        {
            printf("CALC DF-col[%d]\r\n",x);
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
                    s = (f_q * f_q + q*q - f_vk * f_vk - v[k]*v[k])/(2*q - 2*v[k]);

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
                while (z[k + 1] < q)
                {
                    k = k + 1;
                }
                df[q][x] = (q - v[k])*(q - v[k]) + img.at<char>(q, x);
            }
        }

        // 
        // Calculate DF for 
        // 
        // Calculate Distance-transform for each row
        //      df(x,y) = min{xp} ((x-xp)^2 + df_{xp}(y))
        //      df(x,y) = min{xp} ((x - xp)^2 + df{xp}(y) )
        //              = min{a} ((x-a)^2 + G(a))
        // 
        //  Y = constant 
        //  H(x) = df(x,y)
        //  G(x) = DF_project_on(x)(y)
        //  => H(x) = min(a) ((a-x)^2 + G(a)) = DF_official(x in Row, G_y)
        //      
        //  df(x,y) = min{xp}()
        //      df(x,y) = min{xp}()
        // 
        for (int y = 0; y<m; ++y)
        {
            printf("CALCDF2[row=%d]\r\n",y);
            int k = 0;
            double s;
            v[k] = 0;
            z[k] = 0;
            z[k+1] = MAX_INFINITE;

            for (int qx=0; qx < n; qx++)
            {
                double f_qx;
                double f_vk;

                do
                {
                    f_qx = df[y][qx];
                    f_vk = df[y][v[k]];
                    s = (f_qx + qx*qx - f_vk - v[k]*v[k])/(2*qx - 2*v[k]);

                    if (s <= z[k])
                    {
                        k = k - 1;
                        continue;
                    }

                } 
                while (s <= z[k]);

                k = k + 1;
                z[k] = s;
                z[k+1] = MAX_INFINITE;
                v[k] = qx;
            }

            k = 0;
            for (int qx = 0; qx < n; qx++)
            {
                while (z[k +1] < qx)
                {
                    k = k + 1;
                }

                df2[y][qx] = ((qx - v[k])*(qx - v[k]) + df[y][v[k]]);
            }
        }

        for (int y = 0; y<m; ++y)
        {
            for (int x = 0; x<n; ++x)
            {
                dst.at<char>(y,x) = (char)df2[y][x];
            }
        }

        VFREE_2D(df, double, m, n);
        VFREE_2D(df2, double, m, n);
        VFREE(v);
        VFREE(z);
    }
}

int CCVCore::distanceTransform_Rotate(cv::Mat img, cv::Mat& dst)
{
    return 0;
}

int CCVCore::sobel(cv::Mat img, cv::Mat&dst)
{
    cv::Mat sobelX  = (cv::Mat_<double>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    cv::Mat sobelY  = (cv::Mat_<double>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
    cv::Mat gx;
    cv::Mat gy;

    dst.create(img.size(), img.type());
    gx.create(img.size(), img.type());
    gy.create(img.size(), img.type());

    printf("Before filter\r\n");
    cv::filter2D(img, gx, -1, sobelX);
    cv::filter2D(img, gy, -1, sobelY);
    printf("After filter\r\n");

    double dx;
    double dy;
    double val;
    double val0;
    double val1;
    double val2;

    if (img.channels() == 1)
    {
        for (int x = 0; x < img.cols; x++)
        {
            for (int y = 0; y<img.rows; ++y)
            {
                dx = gx.at<uchar>(y,x);
                dy = gy.at<uchar>(y,x);

                val = sqrt(dx*dx + dy*dy);
                dst.at<uchar>(y,x) = val;
            }
        }
    }
    else if (img.channels() == 3)
    {
        Mat_<Vec3b> _gx = gx;
        Mat_<Vec3b> _gy = gy;
        Mat_<Vec3b> _dst = dst;

        for (int x = 0; x < img.cols; x++)
        {
            for (int y = 0; y<img.rows; ++y)
            {
                dx = _gx(y,x)[0];
                dy = _gy(y,x)[0];
                val0 = sqrt(dx*dx + dy*dy);

                dx = _gx(y,x)[1];
                dy = _gy(y,x)[1];
                val1 = sqrt(dx*dx + dy*dy);

                dx = _gx(y,x)[2];
                dy = _gy(y,x)[2];
                val2 = sqrt(dx*dx + dy*dy);

                _dst(y,x)[0] = val0;
                _dst(y,x)[1] = val1;
                _dst(y,x)[2] = val2;
                
            }
        }
    }

    return 0;
}

int CCVCore::gaussianPyramid(cv::Mat img, cv::Mat& dst)
{
    cv::Mat gaussKernel = (cv::Mat_<double>(4, 4) << 1, 4, 6, 4, 1,
                                                        4, 16, 24, 16, 4,
                                                        6, 24, 36, 24, 6,
                                                        4, 16, 24, 16, 4,
                                                        1, 4, 6, 4, 1)/16;
    cv::Mat gaussImg;
    gaussImg.create(img.size(), img.type());

    cv::filter2D(img, gaussImg, img.depth(), gaussKernel);
    
    // Remove even column & rows
    // X = 1 -> N
    // Y = 1 -> M
    int m = img.rows();
    int n = img.cols();
    
    // 
    // Remove columns 2,4,6,... (one index)
    // Remove rows 2,4,6,...    (one index)
    //
    //  
    // 0 => 0
    // 1 => 1
    // 2 => 1
    // 3 => 1,3

    // 
    // If (n is odd ) => [ 1, 2, 3 ] => n / 2 + 1
    // If (n is even ) => [ 1, 2, 3, 4 ] => n/2
    // 
    // => newN = ceil(n/2)
    // 
    int newW = ceil(n/2);
    int newH = ceil(m/2);
    dst.create(
        cv::Size(newW, newH),
        img.type()
    );

    for (int y=0; y < newH; ++y)
    {
        for (int x=0; x<newW; ++x)
        {

        }
    }



    return 0;
}