#include "CProbabilityUtil.h"

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