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