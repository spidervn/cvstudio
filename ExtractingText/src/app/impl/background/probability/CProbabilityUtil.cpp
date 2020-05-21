#include "CProbabilityUtil.h"
#include <bits/stdc++.h>

CProbabilityUtil::CProbabilityUtil(/* args */)
{
}

CProbabilityUtil::~CProbabilityUtil()
{
}

int CProbabilityUtil::bayesUpdateTable(int n, 
                            std::vector<double>& vPrior,
                            std::vector<double>& vLikeLiHood,
                            std::vector<double>& vPost)
{
    double pData = 0;
    for (int i=0; i<n; ++i)
    {
        pData += vPrior[i]*vLikeLiHood[i];
    }

    for (int i=0; i<n; ++i)
    {
        double dPost = vPrior[i]*vLikeLiHood[i] / pData;
        vPost.push_back(dPost);
    }

    // 
    // Posterior = P(H|D)
    //  

    return 0;
}

double CProbabilityUtil::gaussianFunction(double mean,
                                double standard_deviation,    // s^2 
                                double x)
{
    double ret =  
                exp( -(x - mean)*(x-mean)/standard_deviation/standard_deviation/2)
                    / sqrt(2*M_PI) 
                    / standard_deviation;

    return ret;
}

double CProbabilityUtil::covariance(const cv::Mat& m, const cv::Mat& m1)
{
    double d = 0.0;
    double mean_X = 0.0;
    double mean_Y = 0.0;
    double E = 0.0;
    int N;

    assert(m.rows == m1.rows);
    assert(m.cols == m1.cols);

    // 1xN Matrix
    if (m.rows == 1)
    {
        N = m.cols;
        for (int x=0;x<N;++x)
        {
            mean_X += m.at<double>(1,x);
            mean_Y += m1.at<double>(1,x);
        }

        mean_X /= N; 
        mean_Y /= N; 

        // 
        // Expected
        // 
        for (int x=0;x<N;++x)
        {
            E += (m.at<double>(1,x) - mean_X) * 
                    (m1.at<double>(1,x) - mean_Y);
        }

        E /= (N*N);
    }
    // Nx1 Matrix
    else 
    {
        int N = m.rows;
        for (int y=0;y<N;++y)
        {
            mean_X += m.at<double>(y,1);
            mean_Y += m1.at<double>(y,1);
        }

        mean_X /= N; 
        mean_Y /= N;

        // 
        // Expected
        // 
        for (int y=0;y<N;++y)
        {
            E += (m.at<double>(y,1) - mean_X)* 
                    (m1.at<double>(y,1) - mean_Y);
        }

        E /= (N*N);        
    }

    return E;
}