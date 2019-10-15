#include "CParametricTemplateVectorApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

CParametricTemplateVectorApp::CParametricTemplateVectorApp(/* args */)
{
}

CParametricTemplateVectorApp::~CParametricTemplateVectorApp()
{
}

// Finish building Ring-projection transform vector
int CParametricTemplateVectorApp::ringProjectionTransform(int m, int n, cv::Mat t, std::vector<double>& v)
{
    // 
    // Ring projection transform
    // t[m,n] 
    //
    Mat mask;

    int R = std::min(m,n);
    std::vector<int> vcount;        // Count number of pixel for each radius r
    int nR = R/2;                   // Dimension of a vector

    RPT_ring_order_matrix(m,n,mask);
    v.reserve(nR);
    vcount.reserve(nR);

    for (int i=0; i<nR; ++i)
    {
        v[i] = 0;
        vcount[i] = 0;
    }

    for (int x=0; x <R; ++x)
    {
        for (int y=0; y < R; ++y)
        {
            int r = mask.at<int>(y,x);
            v[r] += t.at<uchar>(y,x);
            vcount[r] += 1;
        }
    }

    for (int i=0; i<nR; ++i)
    {
        if (vcount[i] > 0)
        {
            v[i] = v[i] / vcount[i];
        }
    }

    return 0;
}

int CParametricTemplateVectorApp::ringProjectionTransform(int dimension, const cv::Mat& pre_ring_orderMatrix, const cv::Mat& t, std::vector<double>& v)
{
    // 
    // Ring projection transform
    //
    int nR = dimension;
    std::vector<int> vcount;        // Count number of pixel for each radius r

    for (int i=0; i<nR; ++i)
    {
        v.push_back(0);
        vcount.push_back(0);
    }

    printf("(dfsfdsds) nR=%d; Pre(%3d,%3d); T(%d,%d)\r\n", nR, 
                        pre_ring_orderMatrix.rows,
                        pre_ring_orderMatrix.cols,
                        t.rows, t.cols);
    for (int y=0; y < pre_ring_orderMatrix.rows; ++y)
    {
        for (int x=0; x < pre_ring_orderMatrix.cols; ++x)
        {
            int r = pre_ring_orderMatrix.at<int>(y,x);
            //printf("(%3d,%3d) ",y,x);
            v[r] += t.at<uchar>(y,x);
            vcount[r] += 1;
        }

        // if (y < 10)
        {
            //printf("\r\n");
        }
    }

    for (int i=0; i<nR; ++i)
    {
        if (vcount[i] > 0)
        {
            v[i] = v[i] / vcount[i];
        }
    }
    return 0;
}

int CParametricTemplateVectorApp::RPT_ring_order_matrix(int m, int n, cv::Mat& masked)
{
    printf("aaaa\r\n");
    int R = std::min(m,n);
    int x_c;
    int y_c;

    x_c = (R - 1) / 2;
    y_c = (R - 1) / 2;

    masked.create( R, R, CV_32SC1);
    printf("created\r\n");

    for (int y=0;y<R;++y)
    {
        for (int x=0;x<R;++x)
        {
            float r = sqrt((x-x_c)*(x-x_c) + (y-y_c)*(y-y_c));
            masked.at<int>(y,x) = (int)r;
        }
    }

    return 0;
}

double CParametricTemplateVectorApp::NC_double(int R, const std::vector<double>& v1, const std::vector<double>& v2)
{
    double d1 = 0;
    double d2 = 0; 

    double dotPr = 0;
    double sumV1 = 0;
    double sumV2 = 0;
    double sum_squareV1 = 0;
    double sum_squareV2 = 0;

    double tmp1;

    for (int i=0;i<R;++i)
    {
        dotPr += v1[i]*v2[i];

        sumV1 += v1[i];
        sumV2 += v2[i];

        sum_squareV1 += v1[i] * v1[i];
        sum_squareV2 += v2[i] * v2[i];
    }
    
    tmp1 = ((R)*dotPr - sumV1 * sumV2);
    d1 = 100 * tmp1 * tmp1;
    d2 = ((R)*sum_squareV1 - sumV1*sumV1) *
            ((R)*sum_squareV2 - sumV2*sumV2);

    return d1/d2;
}

int CParametricTemplateVectorApp::run(int argc, char const *argv[])
{
    printf("OK\r\n");
    int numScale = 3;
    int n = numScale;
    int R;
    vector<double> vratio({ 1, 0.5, 0.3});          // Test Ratio
    vector<double> ptv;                             // Parametric template vector
    vector<Mat> vTp;                                // Templates
    vector<vector<double>> vecP;
    vector<vector<double>> vH;
    vector<double> vRPV_O;
    vector<Mat> vRingOrder;
    cv::Mat ringOrder;
    cv::Mat H;
    cv::Mat Hinv;
    cv::Mat w;
    cv::Mat G;
    cv::Mat src;
    cv::Mat res;                                // Template matching result
    cv::Mat res_norm;
    cv::Mat subImg;

    vTp.push_back( imread("g_google_templ.png", IMREAD_GRAYSCALE));
    vTp.push_back( imread("g_google_templ_50percent.png", IMREAD_GRAYSCALE));
    vTp.push_back( imread("g_google_templ_30percent.png", IMREAD_GRAYSCALE));
    src = imread("google_multi.png", IMREAD_GRAYSCALE);

    int width = vTp[0].cols;
    int height = vTp[0].rows;
    R = (std::min(width,height)) / 2;

    H.create( n , n , CV_32FC1);
    w.create( n , 1, CV_32FC1);
    G.create( n , 1, CV_32FC1);

    for (int i=0; i<n; ++i)
    {
        printf("Ring order %d; (%d,%d)\r\n", i, vTp[i].rows, vTp[i].cols);
        cv::Mat mRing;

        RPT_ring_order_matrix(vTp[i].rows, vTp[i].cols, mRing);
        vRingOrder.push_back(mRing);
    }

    printf("OK R=%d; (w,h) = (%d,%d)\r\n", R, width, height);

    for (int i=0; i<n; ++i)
    {
        vecP.push_back(std::vector<double>({}));        
    }

    for (int i=0; i<n; ++i)
    {
        ringProjectionTransform(R, vRingOrder[i], vTp[i], vecP[i]);
    }

    for (int i=0; i<n; ++i)
    {
        printf("Vec[%d].size=%d\r\n", i, vecP[i].size());
    }
    
    printf("ok2\r\n");
    // 
    // Scaling value sv
    // 
    // Calculating vector W
    // 
    for (int y=0; y < n ;++y)
    {
        for (int x=0; x < n ; ++x)
        {
            H.at<float>(y,x) = NC_double(R, vecP[y], vecP[x]);
        }
    }

    Hinv = H.inv();

    if (src.rows > height && src.cols > width)
    {
        res = Mat::zeros(src.rows - height, src.cols - width, CV_32FC1);

        for (int y=0; y < res.cols; ++y)
        {
            for (int x=0; x<res.rows; ++x)
            {
                subImg = cv::Mat(src, Rect( y, x, res.cols, res.rows));

                // Calculate G
                ringProjectionTransform(R, vRingOrder[0], subImg, vRPV_O);
                
                for (int i=0; i<n; ++i)
                {
                    G.at<float>(i,0) = NC_double(R, vRPV_O, vecP[i]);
                }

                // Calculate w
                double sumW = 0;
                w = Hinv * (G);

                for (int i=0; i<n; ++i)
                {
                    sumW += w.at<float>(i,0);
                }

                w = w/sumW;
                // 
                // Reconstruct a PTV
                //
                double ptvLen=0;
                for (int i=0; i<R; ++i)
                {
                    ptv[i] = 0;
                    for (int j=0; j<n; ++j)
                    {
                        ptv[i] += vecP[j][i] * w.at<float>(j,0);
                    }

                    ptvLen += ptv[i]*ptv[i];
                }

                ptvLen = sqrt(ptvLen);
                for (int i=0; i<n; ++i)
                {
                    ptv[i] /= ptvLen;
                }

                double NC = NC_double(R, ptv, vRPV_O);
                res.at<float>(y,x)  = NC;
            }
        }
    }

    const char* szSource = "Source";
    const char* szRes = "Result";
    normalize(res, res_norm, 0, 1, NORM_MINMAX, -1, Mat());

    imshow(szSource, src);
    imshow(szRes, res_norm);

    waitKey();
    return 0;
}