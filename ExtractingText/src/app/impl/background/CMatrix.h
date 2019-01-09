#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_CMATRIX_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_CMATRIX_H_

#include <app/interface/background/IMatrix.h>
#include <vector>

class CMatrix : public IMatrix
{
public:
    virtual ~CMatrix();

    double dotProduct(std::vector<double> p1, std::vector<double> p2, int n);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_