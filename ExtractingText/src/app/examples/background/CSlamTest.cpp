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
    return rotate2D();
    return rigid3d_transformation();

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

    // 
    // Multi variate normal distribution
    //
    // Calculating the Multi-variate Gaussian distribution.
    // 

    cv::Mat mtx_Covariance; // nxn
    cv::Mat mtx_Mi;         // nx1
    cv::Mat mtx_x;              // nx1
    cv::Mat mtx_sub = mtx_Mi - mtx_x;   // subtraction
    cv::Mat mtx_sub_T;                  // subtraction transpose

    cv::transpose(mtx_sub, mtx_sub_T);
    
    // double d1 = cv::determinant(2*CV_PI*mtx_Covariance);
    // 
    // Calculates normal distribution
    // 

    // 2D transformation 

    // 
    // Generate the Solution
    // 
    RNG rng;
    int n = 3;     // Number of states
    int m = 2;      // Number of control
    int T = 3;

    A_t.create(n, n, CV_64FC1);     // n x n matrix 
    B_t.create(n, m, CV_64FC1);     // n x m matrix
    e_t.create(n, 1, CV_64FC1);     // n x 1 matrix
    u_t.create(m, 1, CV_64FC1);     // m x 1 matrix
    x_t_1.create(n, 1, CV_64FC1);
    x_t.create(n, 1, CV_64FC1);

    // Random values for test
    random_matrix(A_t, rng);
    random_matrix(B_t, rng);
    random_matrix(x_t_1, rng);

    cout << "Start test:"    << endl;
    cout << "\tA[t]= " << A_t << endl;
    cout << "\tB[t]= " << B_t << endl;
    cout << "\tX[0]= " << x_t_1 << endl;

    for (int t=1; t<=T; ++t)
    {
        random_matrix(e_t, rng);
        random_matrix(u_t, rng);
        cout << "At t = " << t << "; E[t]= " << e_t << "; U[t]= " << u_t << endl;
        x_t = A_t*x_t_1 + B_t * u_t + e_t;
        cout << "We have X[t]= " <<  x_t << endl;

        x_t_1 = x_t;
    }

    return 0;
}

int CSlamTest::random_matrix(cv::Mat& m, cv::RNG& rng)
{
    for (int y=0; y<m.rows;++y)
    {
        for (int x=0; x<m.cols;++x)
        {
            if (m.type() == CV_64FC1)
            {
                printf("HERE");
                m.at<double>(y, x) = (rng.next() % 100) - 50;
            }
            
        }
    }
    return 0;
}

int CSlamTest::test_transformation()
{
    cv::Mat P = (cv::Mat_<double>(3, 1) <<  1, 1, 1 );
    //cv::Mat M_Translate = (cv::Mat_<double>(3, 3 ) << );
    cv::Mat P1 = (cv::Mat_<double>(3,1) << 1, 0, 1);
    cv::Mat P2;

    cv::transpose(P1, P2);

    cv::Mat mm = P * P2;
    cout << mm << endl;

    // Rotation 
    mm.at<double>(1, 0) = 1.1;
    return 0;
}

int CSlamTest::rigid3d_transformation()
{
    // G in SE(3)

    // Rotation and translation
    cv::Mat g = (
        cv::Mat_<double>(4,4) <<
            0, 0, 0, 10,
            0, 0, 0, 2,
            0, 0, 0, 3,
            0, 0, 0, 1
    );

    cv::Mat g1 = g.colRange(3,4);

    cv::Mat x = (
        cv::Mat_<double>(4,1) << 
            1, 1, 1, 1
    );

    cv::Mat dest;
    cv::Mat dest1;

    dest =  g * x;
    dest1 = x + g1;
    
    // cv::sum(dest!=dest1) == cv::Scalar(0,0,0,0)
    // MYASSERT((MATRIX_EQUAL(dest, dest1)), "MOVE OK", "MOVE FAILED");
    if (MATRIX_EQUAL(dest,dest1))
    {
        printf("Movement OK\r\n");
    }
    else
    {
        printf("Movement failed\r\n");
        cout << dest << endl;
        cout << dest1 << endl;
    }

    std::cout << "Matrix = " <<  g << endl;
    std::cout << "Matrix col = " << g1 << endl;

    //
    // 3D rigid body transformations 
    // 
    // Projective transformation

    return 0;
}

int CSlamTest::translation_pos(cv::Mat m, cv::Mat m_trans)
{
    int N = m.rows;

    assert(m.cols == 1);
    assert(m.rows == m_trans.rows);
    assert(m.cols == m_trans.cols);


    cv::Mat result = m + m_trans;
    cout << result << endl;

    return 0;
}

int CSlamTest::rotate2D()
{
    double theta = CV_PI/2;
    cv::Mat point = (cv::Mat_<double>(2,1) << 2, 1);
    cv::Mat m = (cv::Mat_<double>(2, 2) << 1, 1, 1, 1);

    m*point;
    cv::RNG rng = cv::RNG(1234);
    
    //
    // Dot product 
    //  v1 dot v2 = 
    // 
    cv::Mat v1;
    cv::Mat v2;
    cv::Mat v3_dot;
    int N = 2;

    v1.create(cv::Size(N,1), CV_64FC1);
    v2.create(v1.size(), v1.type());

    for (int i=0;i<N;++i)
    {
        v1.at<double>(i,0) = rng.next() % 10;
        v2.at<double>(i,0) = rng.next() % 10;
    }

    v3_dot = v1.mul(v2);
    cout << "Dot product" << endl;
    cout << v1 << endl;
    cout << v2 << endl;
    cout << v3_dot << endl;


    // Theta rotation Anti-clockwise
    cv::Point2d p1;
    cv::Point2d p2;

    // Rotation fact
    //  F01. Same len
    //  
    double angle_origin;
    double len;

    double x = len * cos(angle_origin);
    double y = len * sin(angle_origin);

    double x1 = len* cos(angle_origin + theta);
    double y1 = len* sin(angle_origin + theta);

    // 
    theta = CV_PI/2;
    cv::Mat R = (
        cv::Mat_<double>(2,2) << 
            cos(theta), -sin(theta),
            sin(theta), cos(theta)
    );


    Mat tv1 = (Mat_<double>(2,1) << 5, 4);
    Mat tv2 = R * tv1;

    cout << tv1 << endl;
    cout << tv2 << endl;
    return 0;
}