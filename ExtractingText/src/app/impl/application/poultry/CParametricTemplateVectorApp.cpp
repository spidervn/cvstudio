#include "CParametricTemplateVectorApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "app/impl/general/CConsole.h"
#include "app/impl/general/CCVConsole.h"

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
    std::vector<double> vcount;        // Count number of pixel for each radius r
    int nR = R/2;                   // Dimension of a vector

    RPT_ring_order_matrix(m,n, &mask, vcount);
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

int CParametricTemplateVectorApp::ringProjectionTransform(int dimension, cv::Mat* pre_ring_orderMatrix, std::vector<double>& vCountInRing, const cv::Mat& t, std::vector<double>& v)
{
    // 
    // Ring projection transform
    //
    int nR = dimension;
    // std::vector<int> vcount;        // Count number of pixel for each radius r

    v.clear();
    for (int i=0; i<nR; ++i)
    {
        v.push_back(0);
    }

    //printf("(dfsfdsds) nR=%d; Pre(%3d,%3d); T(%d,%d)\r\n", nR, 
    //                    pre_ring_orderMatrix->rows,
    //                    pre_ring_orderMatrix->cols,
    //                    t.rows, t.cols);
    //printf("xxx");
    for (int y=0; y < pre_ring_orderMatrix->rows; ++y)
    {
        for (int x=0; x < pre_ring_orderMatrix->cols; ++x)
        {
            if (y < 1)
            {
                //printf("(%3d,%3d) ",y,x);
            }
            int r = pre_ring_orderMatrix->at<int>(y,x);

            if (r >= dimension)
            {
                printf("OutRangeEEEEEEEEEEEEEEEE: r=%d, R=%d\r\n", r, dimension);
            }
            
            v[r] += t.at<uchar>(y,x);
        }

        if (y < 1)
        {
            //printf("\r\n");
        }
    }

    for (int i=0; i<nR; ++i)
    {
        if (vCountInRing[i] > 0)
        {
            v[i] = v[i] / vCountInRing[i];
        }
    }

    return 0;
}

int CParametricTemplateVectorApp::RPT_ring_order_matrix(int m, int n, cv::Mat* masked, vector<double>& vCountInRing)
{
    printf("aaaa\r\n");
    int R = std::min(m,n);
    int x_c;
    int y_c;

    x_c = (R - 1) / 2;
    y_c = (R - 1) / 2;

    vCountInRing.clear();

    for (int i=0; i<R; ++i)
    {
        vCountInRing.push_back(0);
    }

    masked->create( R, R, CV_32SC1);
    printf("created\r\n");

    for (int y=0;y<R;++y)
    {
        for (int x=0;x<R;++x)
        {
            double r = sqrt((x-x_c)*(x-x_c) + (y-y_c)*(y-y_c));
            masked->at<int>(y,x) = (int)r;

            vCountInRing[r] += 1;
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

    if(d2 == 0)
    {
        printf("Zero DIVISION\r\n");
    }

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
    vector<vector<double>> vCountInRing;
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
    src = imread("google_multi_300.png", IMREAD_GRAYSCALE);

    // 
    // cv::Mat src_10_100 = src(cv::Rect(10,100,60,50));
    // cv::Mat src_100_10 = src(cv::Rect(100,10,60,50));
    // imwrite("google_multi_10_100.png", src_10_100);
    // imwrite("google_multi_100_10.png", src_100_10);
    //
    // return 0;
    // 

    int width = vTp[0].cols;
    int height = vTp[0].rows;
    R = (std::min(width,height));

    H.create( n , n , CV_64FC1);
    w.create( n , 1, CV_64FC1);
    G.create( n , 1, CV_64FC1);

    for (int i=0; i<R; ++i)
    {
        ptv.push_back(0);
    }

    for (int i=0; i<n; ++i)
    {
        vCountInRing.push_back(std::vector<double>());
    }

    for (int i=0; i<n; ++i)
    {
        printf("Ring order %d; (%d,%d)\r\n", i, vTp[i].rows, vTp[i].cols);
        cv::Mat mRing;

        RPT_ring_order_matrix(vTp[i].rows, vTp[i].cols, &mRing, vCountInRing[i]);
        vRingOrder.push_back(mRing);


        printf("Ring Order(%d) \r\n", i);
        cout << mRing << endl;

        printf("vCountInRing\r\n");
        CConsole::print(vCountInRing[i]);
    }

    printf("OK R=%d; (w,h) = (%d,%d)\r\n", R, width, height);

    for (int i=0; i<n; ++i)
    {
        vecP.push_back(std::vector<double>({}));        
    }

    for (int i=0; i<n; ++i)
    {
        ringProjectionTransform(R, &vRingOrder[i], vCountInRing[i], vTp[i], vecP[i]);
    }

    for (int i=0; i<n; ++i)
    {
        printf("Vec[%d].size=%d\r\n", i, vecP[i].size());
    }

    // 
    // printf("ok2\r\n");
    // 
    // Scaling value sv
    // 
    // Calculating vector W
    // 
    for (int y=0; y < n ;++y)
    {
        for (int x=0; x < n ; ++x)
        {
            H.at<double>(y,x) = NC_double(R, vecP[y], vecP[x]);
        }
    }

    Hinv = H.inv();

    printf("Matrix H\r\n");
    cout << H << endl;

    printf("Matrix H-invert\r\n");
    cout << Hinv << endl;

    if (src.rows > height && src.cols > width)
    {
        res = Mat::zeros(src.rows - height, src.cols - width, CV_32FC1);

        // printf("Res(%d,%d)\r\n", res.cols, res.rows);
        for (int y=0; y < res.cols; ++y)
        {
            for (int x1 = 0; x1 < res.rows; ++x1)
            {
                // subImg = src(Rect(x, y, width, height));
                subImg = src(Rect(x1, y, width, height));
                // printf("(%d,%d); ",x , y);

                // 
                // Calculate G
                // printf("*(*(*\r\n");
                // 
                ringProjectionTransform(R, &vRingOrder[0], vCountInRing[0], subImg, vRPV_O); // subImg

                if (x1 % 150 == 0)
                {
                    printf("process: %d; ", x1);
                }

                for (int i=0; i<n; ++i)
                {
                    /*
                    for (int j=0; j<R; ++j)
                    {
                        double dd = vecP[i][j];
                        double dd1 = vRPV_O[0];
                    }
                    */
                    
                    //printf("StartCalc\r\n");
                    G.at<double>(i,0) = NC_double(R, vRPV_O, vecP[i]);
                    // printf("NC_double(%d)\r\n", i);
                }

                //printf("*(*(*22\r\n");
                // Calculate w
                double sumW = 0;
                w = Hinv * (G);


                if (y < 10 && x1==0)
                {
                    printf("vector G at(%d,%d)\r\n", y, x1);

                    cout << G << endl;
                    printf("Vector w\r\n");
                    cout << w << endl;
                }


                for (int i=0; i<n; ++i)
                {
                    sumW += w.at<double>(i,0);
                }

                w = w/sumW;

                if ( x1 % 150 == 151 )
                {
                    printf("Matrix G\n");
                    cout << G << endl;

                    printf("Matrix H: \r\n");
                    // CCVConsole::printMatrix<double>(H);
                    cout << H << endl;
                    printf("\r\n");
                    printf("Matrix H-invert: \r\n");
                    // CCVConsole::printMatrix<double>(Hinv);
                    cout << Hinv << endl;
                    printf("\r\n");
                    cv::Mat hTest = H * Hinv;
                    printf("I\r\n");
                    // CCVConsole::printMatrix<double>(hTest);
                    cout << hTest << endl;
                    printf("\r\n");

                    printf("Found w: press key...\r\n\t");
                    for (int i=0;i<n;++i)
                    {
                        printf("%f; ", w.at<double>(i,0));
                    }
                    printf("\r\n");
                    // waitKey();
                }
                
                // 
                // Reconstruct a PTV
                //
                double ptvLen=0;
                for (int i=0; i<R; ++i)
                {
                    ptv[i] = 0;
                    for (int j=0; j<n; ++j)
                    {
                        ptv[i] += vecP[j][i] * w.at<double>(j,0);
                    }

                    ptvLen += ptv[i]*ptv[i];
                }

                ptvLen = sqrt(ptvLen);
                for (int i=0; i<n; ++i)
                {
                    ptv[i] /= ptvLen;
                }

                if (x1 % 150 == 0 && y == 0)
                {
                    printf("PTV\r\n");
                    CConsole::print(ptv);
                }

                double NC = NC_double(R, ptv, vRPV_O);
                res.at<double>(y,x1)  = NC;
            }
            
            printf("ONE %d\r\n", y);
        }
    }

    const char* szSource = "Source";
    const char* szRes = "Result";
    const char* szResRaw = "Result-Raw";

    printf("Normalize \r\n");
    normalize(res, res_norm, 0, 1, NORM_MINMAX, -1, Mat());
    printf("Normalize22 \r\n");

    double minVal; 
    double maxVal; 
    Point minLoc; 
    Point maxLoc;
    minMaxLoc(res_norm, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    rectangle(src, maxLoc, cv::Point( maxLoc.x + width, maxLoc.y + height), Scalar(0,255,255));

    printf("Fit-location (%d,%d); valNorm=%f; valRaw=%f\r\n", 
                            maxLoc.x, maxLoc.y, 
                            res_norm.at<double>(maxLoc.y, maxLoc.x), 
                            res.at<double>(maxLoc.y, maxLoc.x));

    namedWindow(szSource, WINDOW_AUTOSIZE);
    namedWindow(szRes, WINDOW_AUTOSIZE);
    namedWindow(szResRaw, WINDOW_AUTOSIZE);

    imshow(szSource, src);    
    imshow(szRes, res_norm);
    imshow(szResRaw, res);

    waitKey();
    return 0;
}