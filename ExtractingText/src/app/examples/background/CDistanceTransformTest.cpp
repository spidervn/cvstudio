#include "CDistanceTransformTest.h"
#include <stdio.h>
#include <stdlib.h>

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
    double v[100];
    double z[100];
    double df[100];     /* Distance transform */
    double s;
    
    k = 0;              /* Index of rightmost parabola in lower envelop */
    v[0] = 0;           /* Locations of parabolas in lower envelope */
    z[0] = -999999;     
    z[1] = 999999;      /* Locations of boundaries between parabolas */

    for (q=1; q<n; q++)
    {
        s = ((function_f(q) + q*q) - (function_f(v[k]) + v[k]*v[k]))/(2*q - 2*v[k]);

        if (s <= z[k])
        {
            k = k - 1;       
        }
        else
        {
            k = k + 1;
            v[k] = q;
            z[k] = s;
            z[k+1] = 999999;
        }
    }

    k = 0;
    for (q=0;q<n;q++)
    {
        while (z[k+1] < q)
        {
            k = k + 1;
        }
        // End of this 
        // z[k+1] >= q

        df[q] = (q - v[k])*(q - v[k]) + function_f(v[k]);
    }

    printf("Result:\r\n");
    for (int i=0;i<n;i++)
    {
        printf("%f,", df[i]);
    }
    printf("\r\n");
}

double CDistanceTransformTest::function_f(double a)
{
    return a + 1;
}