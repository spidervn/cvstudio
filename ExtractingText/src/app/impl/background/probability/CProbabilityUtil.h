#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_PROBABILITY_CPROBABILITYUTIL_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_PROBABILITY_CPROBABILITYUTIL_H_

#include <app/interface/background/probability/IProbabilityUtil.h>

#define CProbabilityUtilPtrNew std::make_shared<CProbabilityUtil>()

class CProbabilityUtil: public IProbabilityUtil
{
private:
    /* data */
public:
    CProbabilityUtil(/* args */);
    virtual ~CProbabilityUtil();

    int bayesUpdateTable(int n, 
                            std::vector<double>& vPrior,
                            std::vector<double>& vLikeLiHood,
                            std::vector<double>& vPost);

    double gaussianFunction(double mean,
                            double standard_deviation,    // s^2 
                            double x);
};


#endif