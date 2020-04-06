#include "CMatrix.h"
/*
 * TODO: 
 */
CMatrix::~CMatrix()
{}

double CMatrix::dotProduct(std::vector<double> p1, std::vector<double> p2, int n)
{
    double ret = 1;
    
    for(int i = 0; i < n; i++)
    {
        ret += p1[i] * p2[i];
    }
    
    return ret;
}

double CMatrix::dotProduct(std::vector<double> p1, 
                                std::vector<double> p2,
                                int n,
                                int step_v1,
                                int step_v2)
{
    return 0;
}

int CMatrix::MatrixProduct(Matrix<double> m1, Matrix<double> m2, Matrix<double>& m_out)
{
    int ret = 1;    // Invalid
    if (m1.cols() == m2.rows())
    {
        // OK
        m_out.Rebuild(m1.rows(), m2.cols());
        int N_SAME = m1.cols();

        for(int i = 0; i < m1.rows(); i++)
        {
            for (int j=0; j<m2.cols();j++)
            {
                // dotProduct(m1.rows())
                double t = IMatrix::dotProduct(m1.rows(i), m2.cols(j), N_SAME, 1, m1.cols());
                m_out.set(i,j,t);
            }
        }
    }
    else
    {        
    }
    
    return ret;
}

// int CMatrix::MatrixProduct()
// {
//     return 0;
// }

double CMatrix::det(Matrix<double> m) 
{
    return 0;
}

double CMatrix::det(const cv::Mat& m) 
{
    assert(m.rows == m.cols);
    assert(m.channels() == 1);

    if (m.rows == 2)
    {
        return 
            m.at<double>(0,0) * m.at<double>(1,1) - 
            m.at<double>(0,1) * m.at<double>(1,0);
    }

    return -1.0;
}