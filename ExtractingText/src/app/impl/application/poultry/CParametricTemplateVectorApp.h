#ifndef EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CPARAMETRICTEMPLATEVECTORAPP_H_
#define EXTRACTTEXT_APP_IMPL_APPLICATION_POULTRY_CPARAMETRICTEMPLATEVECTORAPP_H_

#include "app/interface/IApplication.h"
#include <opencv2/core.hpp>
#include <vector>

class CParametricTemplateVectorApp: public IApplication
{
private:
    /* data */
public:
    CParametricTemplateVectorApp(/* args */);
    ~CParametricTemplateVectorApp();

    int ringProjectionTransform(int m, int n, cv::Mat t, std::vector<double>& v);    
    int ringProjectionTransform(int dimension, cv::Mat* pre_ring_orderMatrix, std::vector<double>& vCountInRing, const cv::Mat& t, std::vector<double>& v);
    int RPT_ring_order_matrix(int m, int n , cv::Mat* masked, std::vector<double>& vCountInRing);
    double NC_double(int N, const std::vector<double>& v1, const std::vector<double>& v2);

    int run(int argc, char const *argv[]);
};

#endif