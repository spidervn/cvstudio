#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_IMATRIX_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_IMATRIX_H_

#include <vector>

class IMatrix
{
public:
    virtual ~IMatrix() {};

    virtual double dotProduct(std::vector<double> p1, 
                                std::vector<double> p2,
                                int n) = 0;
};

#endif