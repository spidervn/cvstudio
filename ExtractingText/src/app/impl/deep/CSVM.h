#ifndef EXTRACTTEXT_APP_IMPL_DEEP_CSVM_H_
#define EXTRACTTEXT_APP_IMPL_DEEP_CSVM_H_

#include <app/interface/IApplication.h>
#include <vector>

typedef std::vector<double> VECTOR;

class CSVM
{
public:
    virtual ~CSVM();

    int gradient_descent(int dimension_ofX, std::vector<VECTOR> v_x, std::vector<double> v_y, std::vector<double> v_theta);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_