#include "CDistanceTransformTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "app/impl/cv/CCVCore.h"

using namespace std;
using namespace cv;

#define STEP_ANALYZE

CDistanceTransformTest::CDistanceTransformTest(/* args */)
{
}

CDistanceTransformTest::~CDistanceTransformTest()
{
}

void CDistanceTransformTest::test_1D()
{
    int k;
    int q;
    int n = 10;
    int v[100];
    double z[100];
    double df[100];     /* Distance transform */
    double s;
    
    k = 0;              /* Index of rightmost parabola in lower envelop */
    v[0] = 0;           /* Locations of parabolas in lower envelope */
    z[0] = -999999;     
    z[1] = 999999;      /* Locations of boundaries between parabolas */

    #ifdef STEP_ANALYZE
    printf("Start Examine DF1D:\r\n");
    printf("Step-Init(k=%d)\r\n:", k);
    printf("\tV=");
    for (int j=0;j<=k;j++)
    {
        printf("%d, ", v[j]);
    }
    printf("\r\n");
    printf("\tZ=");
    for (int j=0;j<=k+1;j++)
    {
        printf("%0.2f, ", z[j]);
    }
    printf("------\r\n");
    getchar();
    #endif

    for (q=1; q<n; q++)
    {
        #ifdef STEP_ANALYZE
        printf("Step-Examine q=%d\r\n:", q);
        #endif
        


        bool bDone = false;
        do 
        {
            s = ((function_f(q) + q*q) - (function_f(v[k]) + v[k]*v[k]))/(2*q - 2*v[k]);

            #ifdef STEP_ANALYZE
            printf("\tParabol(root-%d) x Parabol(root-%d) at x = %0.2f\r\n", q, v[k], s);
            #endif


            if (s <= z[k])
            {
                #ifdef STEP_ANALYZE
                printf("\t%0.2f <= %0.2f (s<=z[%d]) => Reduce k=%d\r\n", s, z[k], k, k-1);
                #endif

                k = k - 1;

                #ifdef STEP_ANALYZE
                printf("\tV=");
                for (int j=0;j<=k;j++)
                {
                    printf("%d, ", v[j]);
                }
                printf("\r\n");
                printf("\tZ=");
                for (int j=0;j<=k+1;j++)
                {
                    printf("%0.2f, ", z[j]);
                }
                printf("------\r\n");
                getchar();
                #endif
            }
            else 
            {
                bDone = true;
            }
        } while (!bDone);

        #ifdef STEP_ANALYZE
        printf("\t%0.2f > %0.2f (s>z[%d]) => Update k=%d\r\n", s, z[k], k, k+1);
        #endif

        k = k + 1;
        v[k] = q;
        z[k] = s;
        z[k+1] = 999999;

        #ifdef STEP_ANALYZE
        printf("\tV=");
        for (int j=0;j<=k;j++)
        {
            printf("%d, ", v[j]);
        }
        printf("\r\n");
        printf("\tZ=");
        for (int j=0;j<=k+1;j++)
        {
            printf("%0.2f, ", z[j]);
        }
        printf("------\r\n");
        getchar();
        #endif

    }

    #ifdef STEP_ANALYZE
    printf("Start-Computing result:\r\n");
    #endif
    k = 0;
    for (q=0;q<n;q++)
    {
        while (z[k+1] < q)
        {
            k = k + 1;
        }
        // End of this 
        // z[k+1] >= q

        #ifdef STEP_ANALYZE
        printf("\tFor (q=%d), k=%d, z[k](%0.2f) <= q < z[k+1](%0.2f)\r\n", q, k, z[k], z[k+1]);
        #endif

        df[q] = (q - v[k])*(q - v[k]) + function_f(v[k]);
    }

    #ifdef STEP_ANALYZE
    printf("\r\n");
    #endif

    printf("Result:\r\n");
    for (int i=0;i<n;i++)
    {
        printf("%f,", df[i]);
    }
    printf("\r\n");
    printf("V[i]=\r\n");
    for (int i=0; i<n; i++)
    {
        printf("%d, ", v[i]);
    }
    printf("\r\n");
}

void CDistanceTransformTest::test_2D(const char* szFile)
{
    Mat img;
    Mat img_gray;
    Mat img_dst;

    const char* szSource = "Source window";
    const char* szDst = "Distance transform";
    const char* szGray = "Gray img";

    img = imread(szFile, IMREAD_COLOR);

    if (img.empty())
    {
        printf("ERRRRRRRRRRRRRRRRRRRRRRRRR\r\n");
    }
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    ICVCore* p = new CCVCore();
    p->distanceTransform(img_gray, img_dst);

    namedWindow(szSource, WINDOW_AUTOSIZE);
    namedWindow(szDst, WINDOW_AUTOSIZE);
    namedWindow(szGray, WINDOW_AUTOSIZE);

    imshow(szSource, img);
    imshow(szGray, img_gray);
    imshow(szDst, img_dst);

    waitKey();
    delete p;
}

void CDistanceTransformTest::bruteForce()
{
    int n = 10;
    double df[100];

    for (int i=0;i<n;i++)
    {
        double min = 999999;

        for (int q = 0; q<n;q++)
        {
            // if (q != i)
            {
                double d = (q - i) * (q-i) + function_f(q);

                if (min > d)
                {
                    min = d;
                }
            }

        }

        df[i] = min;
    }

    printf("BruteForce for finding DF: ");
    for (int i=0;i<n;i++)
    {
        printf("(%d,%f); ", i, df[i]);
    }
    printf("\r\n");
}

double CDistanceTransformTest::function_f(double a)
{
    double arr[] = 
    {
        100, 7, 8, 67, 100,
        7, 4, 87, 22, 23,
        45, 55, 1, 9, 0
    };
    int i = a;
    int n = sizeof(arr)/sizeof(arr[0]);
    return arr[i];
}