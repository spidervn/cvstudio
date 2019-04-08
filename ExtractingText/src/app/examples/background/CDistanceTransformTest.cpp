#include "CDistanceTransformTest.h"

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
        
    }
}

double CDistanceTransformTest::function_f(double a)
{
    return a + 1;
}