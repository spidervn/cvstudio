#include "CCVCore.h"

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#define VMALLOC(v, type, element_size) v = (type*)malloc(sizeof(type) * element_size)
#define VFREE(v) free(v)
#define VMALLOC_2D(v, type, row, col) v = (type**)malloc(sizeof(type*) * row); for (int yyyyy000=0;yyyyy000<row;yyyyy000++) { v[yyyyy000] = (type*) malloc(sizeof(type) * col); }
#define VFREE_2D(v, type, row, col) for (int yyyyy000=0;yyyyy000<row;yyyyy000++) { free(v[yyyyy000]); } free(v);

using namespace cv;
using namespace std;

CCVCore::CCVCore()
{}

CCVCore::~CCVCore()
{}

int CCVCore::calc_Gaussian1DKernel(int n, cv::Mat& out)
{
    //
    // Gaussian Function
    //  GF(x) = 1/
    //  GF(x)  =
    //      1/(σ*√(2π)) * exp(-1/2 * ((x-μ)/σ)^2)

    // 
    // x = [0,1,...,n-1]
    // 
    // Var(X) = E((X-mean)^2).
    // 
    if (n<=0 || n > 1000000)
    {
        throw "Out of range";
        return -1;
    }


    double std_variantion = 0;
    double mean;
    double SUM = 0;
    mean = (n-1)/2;

    // Calculates standard deviation and Mean
    for (double i=0;i<= n-1;i++)
    {
        SUM += (i-mean)*(i-mean);
    }
    SUM = SUM / n;

    std_variantion = sqrt(SUM);

    out.create(cv::Size(1,n), CV_64FC1);

    for (double i=0; i<=n-1; ++i)
    {
        double e_pow = (i - mean) / std_variantion;
        out.at<double>(0,i) = 1/(std_variantion * sqrt(2*CV_PI)) * exp( -e_pow*e_pow/2);
    }

    return 0;
}

int CCVCore::calc_Gaussian2DKernel(int n, cv::Mat& out)
{
    if (n<=0 || n > 1000000)
    {
        throw "Out of range";
        return -1;
    }


    /*--------------------------------------------------
        Variance:
            VAR = E((x-mean)^2)
    *--------------------------------------------------*/
    //
    double std_variantion;
    double mean_x;
    double mean_y;
    double mean;
    
    mean_x = (n-1)/2;
    mean_y = (n-1)/2;

    // Calculates VARIANCES 
    double sum = 0;
    for (double y=0; y<=n-1; ++y)
    {
        for (double x=0; x<=n-1; ++x)
        {
            double diff = (x - mean_x) + (y - mean_y);
            sum += diff * diff;
        }
    }

    std_variantion = sqrt(sum);
    out.create(cv::Size(n,n), CV_64FC1);

    for (double y=0; y<=n-1; ++y)
    {
        for (double x=0; x<=n-1; ++x)
        {
            double e_pow = (x - mean_x + y - mean_y) / std_variantion;
            out.at<double>(y,x) = 
                1/sqrt(2*CV_PI)/std_variantion * 
                exp(
                    -e_pow*e_pow/2
                );
        }
    }


    return 0;
}

int CCVCore::dodge(cv::Mat front, cv::Mat back, cv::Mat& res)
{
    // res.create(front.size(), CV_32FC1);
    //res = front * 255 / (255 - back);
    //res.setTo(255 , res > 255);
    //res.setTo(255, back == 255);

    //@Temp code
    printf("Dodge [%d,%d]\r\n", front.rows, front.cols);

    res.create(front.size(), CV_8UC1);

    for (int y=0; y<front.rows;++y)
    {
        for (int x=0; x<front.cols; ++x)
        {
            if (255 - back.at<uchar>(y,x) == 0)
            {
                res.at<uchar>(y,x) = 255;
            }
            else 
            {
                float f = front.at<uchar>(y,x) * 255 / (255 - back.at<uchar>(y,x));

                if (f > 255)
                {
                    res.at<uchar>(y,x) = 255;
                }
                else if (back.at<uchar>(y,x) == 255)
                {
                    res.at<uchar>(y,x) = 255;
                }
                else
                {
                    res.at<uchar>(y,x) = (uchar)f;
                }
            }

            
        }
        printf("oneline %d\r\n", y);
    }
    printf("Dodge\r\n");

    return 0;
}

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

int CCVCore::contourRect(const std::vector<cv::Point>& v, cv::Rect& r)
{
    r = Rect(-1,-1,-1,-1);
    
    //
    // Trick: use width & height to store (right, bottom)
    //
    for (int i=0; i<v.size(); ++i)
    {
        if (r.x == -1)
        {
            r.x = v[i].x;
        }
        else if (v[i].x < r.x)
        {
            r.x = v[i].x;
        }
        if (r.width == -1)
        {
            r.width = v[i].x;
        }
        else if (r.width < v[i].x)
        {
            r.width = v[i].x;
        }            

        if (r.y == -1)
        {
            r.y = v[i].y;
        }
        else if (v[i].y < r.y)
        {
            r.y = v[i].y;
        }

        if (r.height == -1)
        {
            r.height = v[i].y;                
        }
        else if ( r.height < v[i].y)
        {
            r.height = v[i].y;
        }
    }

    // Un-trick
    r.width = r.width - r.x;
    r.height = r.height - r.y;
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
    // PryDown
    cv::Mat gaussKernel = (cv::Mat_<double>(5,5) << 1, 4, 6, 4, 1,
                                                        4, 16, 24, 16, 4,
                                                        6, 24, 36, 24, 6,
                                                        4, 16, 24, 16, 4,
                                                        1, 4, 6, 4, 1)/256;
    cv::Mat gaussImg;
    cv::Mat dstStep1; // Intermediate matrix
    cv::Mat dstStep1_90;
    cv::Mat dstStep2_90;

    gaussImg.create(img.size(), img.type());
    cv::filter2D(img, gaussImg, img.depth(), gaussKernel);
    
    // Remove even column & rows
    // X = 1 -> N
    // Y = 1 -> M
    int m = img.rows;
    int n = img.cols;

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
    // 
    // If (n is odd ) => [ 1, 2, 3 ] => n / 2 + 1
    // If (n is even ) => [ 1, 2, 3, 4 ] => n/2
    // 
    // => newN = ceil(n/2)
    //
    int newW = ceil(n/2);
    int newH = ceil(m/2);

    dstStep1.create(cv::Size(n, newH), img.type());
    dstStep2_90.create(cv::Size(newH, newW), img.type());
    dst.create(
        cv::Size(newW, newH),
        img.type()
    );
    
    unsigned char* pOrigin = gaussImg.data;
    unsigned char* pStep1 = dstStep1.data;
    unsigned char* pDst = dst.data;
    int rowsize = n * img.channels();

    // Step-01
    // Copy every even rows
    for (int row=0; row < newH; ++row)
    {
        memcpy(pStep1 + rowsize * row  , pOrigin + rowsize * (2*row + 1), rowsize);
    }

    // 
    // Step02 => copy columns data
    //      From pStep1 to pOrigin
    // 
    cv::rotate(dstStep1, dstStep1_90, ROTATE_90_CLOCKWISE);
    
    unsigned char* pStep1_90;
    unsigned char* pStep2_90;

    pStep1_90 = dstStep1_90.data;
    pStep2_90 = dstStep2_90.data;

    rowsize = dstStep2_90.cols *  img.channels();
    // Copy every-line
    for (int y=0; y< dstStep2_90.rows; ++y)
    {
        memcpy(pStep2_90 + rowsize * y, pStep1_90 + rowsize*(2*y+1), rowsize);
    }

    cv::rotate(dstStep2_90, dst, ROTATE_90_COUNTERCLOCKWISE);

    return 0;
}

int CCVCore::gaussianPyramidUp(cv::Mat img, cv::Mat& dst)
{
    // Origin size
    int orgRows = img.rows;
    int orgCols = img.cols;

    /* 
     * 1- imgExt2 = new double-size Img 
     * 
     * Construct <=> 
     * <=> How do you add Even rows & columns.
     * 
     */

    cv::Mat gaussKernel = (cv::Mat_<double>(5,5) << 1, 4, 6, 4, 1,
                                                        4, 16, 24, 16, 4,
                                                        6, 24, 36, 24, 6,
                                                        4, 16, 24, 16, 4,
                                                        1, 4, 6, 4, 1) / 64;
    
    cv::Mat img2;
    img2.create(cv::Size(2*orgCols, 2*orgRows), img.type());
    
    // Dummy code
    if (img.channels() == 1)
    {
        for (int y=0; y<orgRows;++y)
        {
            for (int x=0; x<orgCols; ++x)
            {
                int twoY = 2*y;
                int twoX = 2*x;
                img2.at<uchar>(twoY, twoX) = img.at<uchar>(y,x);
                img2.at<uchar>(twoY + 1, twoX) = 0;
                img2.at<uchar>(twoY + 1, twoX + 1) = 0;
                img2.at<uchar>(twoY, twoX + 1) = 0;
            }
        }
    }
    else if (img.channels() == 3)
    {
        Mat_<Vec3b> _I = img;
        Mat_<Vec3b> _I2 = img2;

        for (int y=0; y<orgRows;++y)
        {
            for (int x=0; x<orgCols; ++x)
            {
                int twoY = 2*y;
                int twoX = 2*x;

                _I2(twoY, twoX)[0] = _I(y,x)[0];
                _I2(twoY, twoX)[1] = _I(y,x)[1];
                _I2(twoY, twoX)[2] = _I(y,x)[2];

                _I2(twoY + 1, twoX)[0] = 0;
                _I2(twoY + 1, twoX)[1] = 0;
                _I2(twoY + 1, twoX)[2] = 0;

                _I2(twoY, twoX + 1)[0] = 0;
                _I2(twoY, twoX + 1)[1] = 0;
                _I2(twoY, twoX + 1)[2] = 0;

                _I2(twoY + 1, twoX + 1)[0] = 0;
                _I2(twoY + 1, twoX + 1)[1] = 0;
                _I2(twoY + 1, twoX + 1)[2] = 0;
            }
        }
    }
    
    // Filled with Zero 
    cv::filter2D(img2, dst, img.depth(), gaussKernel);

    return 0;
}

int CCVCore::canny(cv::Mat img, cv::Mat& dst)
{
    /* 
     * Steps 
     *  1- Gaussian 
     *  2- Find the intensity gradients
     *  3- Apply non-maximum 
     *  4- Apply double threshold 
     *  5- Track edge by hyteresis
     */
    //1- Gaussian
    // 

    return 0;
}

int CCVCore::bucketingColor(cv::Mat img, int range, cv::Mat& dst)
{
    int nchnn = img.channels();
    dst.create(img.size(), img.type());

    if (nchnn == 1)
    {
        for (int y=0; y<img.rows; ++y)
        {
            for (int x=0; x<img.cols;++x)
            {
                uchar u = img.at<uchar>(y,x);
                uchar u_new = (u / range) * range;
                dst.at<uchar>(y,x) = u_new;
            }
        }
    }
    else if (nchnn == 3)
    {
        Mat_<Vec3b> I_ = img;
        Mat_<Vec3b> I2_ = dst;
        for (int y=0; y<img.rows; ++y)
        {
            for (int x=0; x<img.cols;++x)
            {
                uchar u0, u1, u2;
                uchar u0n, u1n, u2n;

                u0 = I_(y,x)[0];
                u1 = I_(y,x)[1];
                u2 = I_(y,x)[2];

                u0n = (u0 / range ) * range;
                u1n = (u1 / range ) * range;
                u2n = (u2 / range ) * range;

                I2_(y,x)[0] = u0n;
                I2_(y,x)[1] = u1n;
                I2_(y,x)[2] = u2n;
            }
        }
    }
    else
    {
        return -1;
    }
    
    return 0;
}

int CCVCore::nextRNG()
{
    return 0;
}

int CCVCore::lehmerRNG(int p, int n, int seed, std::vector<int>& v)
{
    int b = 10;
    v.clear();
    v.push_back(seed);

    for (int i=1; i<n; ++i)
    {
        int nNW = (b * v[v.size()-1]) % p;
        v.push_back(nNW);
    }

    return 0;
}

int CCVCore::convexHull(std::vector<std::vector<cv::Point>> contours, std::vector<cv::Point>& vhull)
{
    vector<Point> v1;
    
    for (int i=0; i<contours.size();++i)
    {
        for (int j=0; j<contours[i].size(); ++j)
        {
            v1.push_back(contours[i][j]);
        }
    }

    vhull.clear();
    cv::convexHull(v1, vhull, true);
    
    return 0;
}