#include "CManualFundamentalApp.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/connected_components.hpp"

#include "app/impl/cv/CCVCore.h"
#include "app/test/cv/CCVCoreUnitTest.h"

using namespace cv;
using namespace boost;
using namespace std;

CManualFundamentalApp::CManualFundamentalApp(/* args */)
{
}

CManualFundamentalApp::~CManualFundamentalApp()
{
}

int CManualFundamentalApp::run(int argc, char const *argv[])
{
    Mat c = (Mat_<double>(3,1) << 1, 2, 3);
    Mat c1 = (Mat_<double>(1,3) << 2, 4, 6);
    Mat c3 = c*c1;

    c3.at<double>(2,1) = 0;
    std::cout << c << std::endl;
    std::cout << c1 << std::endl;
    std::cout << c3 << std::endl;

    Mat m_gaussKernel;

    ICVCorePtr ccptr = CCVCorePtrNew();
    CCVCoreUnitTest cvtest;

    ccptr->calc_Gaussian1DKernel(100, m_gaussKernel);
    cout << "Gauss1DKernel " << m_gaussKernel << endl;

    cvtest.checkValid_gaussianKernel(m_gaussKernel);

    return 0;
}