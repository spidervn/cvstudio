#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_CMATRIX_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_CMATRIX_H_

#include <app/interface/background/IMatrix.h>
#include <vector>

class CMatrix : public IMatrix
{
public:
    virtual ~CMatrix();

    double dotProduct(std::vector<double> p1, std::vector<double> p2, int n);

    double dotProduct(std::vector<double> p1, 
                                std::vector<double> p2,
                                int n,
                                int step_v1=1,
                                int step_v2=1);

    int  MatrixProduct(Matrix<double> m1, Matrix<double> m2, Matrix<double>& m_out);
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_