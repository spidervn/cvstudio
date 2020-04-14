#include "CSlamTest.h"

#include <iostream>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

CSlamTest::CSlamTest(/* args */)
{
}

CSlamTest::~CSlamTest()
{
}

int CSlamTest::run(int argc, char const *argv[])
{
    cv::Mat C = (Mat_<double>(1, 3) << 1, 2, 1);
    cv::Mat D = (Mat_<double>(3, 1) << 1, 2, 1);
    cv::Mat D1 = (Mat_<double>(3, 3) << 1, 2, 1, 2, 3, 2, 3, 4, 3);

    cv::Mat E = C * D1;

    cout << C << endl;
    cout << D << endl;
    cout << D1 << endl;
    cout << E << endl;

    // **************
    // Linear function with Gaussian noise 
    cv::Mat x_t;
    cv::Mat x_t_1;
    cv::Mat A_t;
    cv::Mat B_t;
    cv::Mat u_t;
    cv::Mat e_t;


    x_t = A_t * x_t_1 + 
            B_t * u_t + 
            e_t;

    // 
    // Multi variate normal distribution
    //
    // Calculating the Multi-variate Gaussian distribution.
    // 

    2* CV_PI;

    cv::Mat mtx_Covariance; // nxn
    cv::Mat mtx_Mi;         // nx1
    cv::Mat mtx_x;              // nx1
    cv::Mat mtx_sub = mtx_Mi - mtx_x;   // subtraction
    cv::Mat mtx_sub_T;                  // subtraction transpose

    cv::transpose(mtx_sub, mtx_sub_T);
    
    double d1 = cv::determinant(2*CV_PI*mtx_Covariance);
    

    // 
    // Calculates normal distribution
    // 
    


    return 0;
}