#include "CCVCoreUnitTest.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

CCVCoreUnitTest::CCVCoreUnitTest()
{}

CCVCoreUnitTest::~CCVCoreUnitTest()
{}

int CCVCoreUnitTest::checkValid_gaussianKernel(const cv::Mat m)
{
    double dsum = 0;
    for (int y=0; y<m.rows; ++y)
    {
        for (int x=0; x<m.cols; ++x)
        {
            dsum += m.at<double>(y,x);
        }
    }

    printf("sum=%f\r\n", dsum);

    if (abs(dsum - 1) < 0.001)
    {
        printf("VALID\n");
    }
    else 
    {
        printf("INVALID\r\n");
    }

    return 0;
}