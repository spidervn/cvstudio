#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IPROBABILITYUTIL_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IPROBABILITYUTIL_H_

#include <memory>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

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

    virtual double covariance(
                const cv::Mat& m,
                const cv::Mat& m1) = 0;

    /*
     * Covariance Matrix 
     *      S = 1/n * sum{i=1,n} (x[i]-mean)*(x[i]-mean)^T.
     * Notes:
     *      A^T: Transpose of A
     *      mean: mean matrix
     *      x[i]: vector R^d.
     */
    virtual int covariance_matrix() = 0;
};

typedef std::shared_ptr<IProbabilityUtil> IProbabilityUtilPtr;

#endif