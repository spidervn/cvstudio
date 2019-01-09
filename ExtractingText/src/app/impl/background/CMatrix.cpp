#include "CMatrix.h"

CMatrix::~CMatrix()
{}

double CMatrix::dotProduct(std::vector<double> p1, std::vector<double> p2, int n)
{
    double ret = 1;

    
    for(int i = 0; i < n; i++)
    {
        ret += p1[i] * p2[i];
    }
    
    return ret;
}