#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IPROBABILITYUTIL_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IPROBABILITYUTIL_H_

#include <memory>
#include <vector>

class IProbabilityUtil
{
public:
    virtual ~IProbabilityUtil() {}

    virtual int bayesUpdateTable(int n, 
                            std::vector<double>& vPrior,
                            std::vector<double>& vLikeLiHood,
                            std::vector<double>& vPost) = 0;

    virtual double gaussianFunction(
            double mean,
            double standard_deviation,    // s^2 
            double x
    ) = 0;

    
};

typedef std::shared_ptr<IProbabilityUtil> IProbabilityUtilPtr;

#endif