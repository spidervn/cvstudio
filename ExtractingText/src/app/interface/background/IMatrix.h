#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_IMATRIX_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_IMATRIX_H_

#include <vector>
#include <stdio.h>   
#include <stdlib.h> 

template <typename T>
class Matrix
{
public:
    Matrix(int rows, int cols)
    {
        m = rows;
        n = cols;

        // Dummiest 
        _p_Data = malloc(m*n*sizeof(T));
    }

    ~Matrix()
    {
        __freeMatrix();
    }

    int Rebuild(int rows, int cols)
    {
        __freeMatrix();

        m = rows;
        n = cols;

        // Dummiest 
        _p_Data = (T*)malloc(m*n*sizeof(T));

    }
   
private:    

    int __freeMatrix()
    {
        if (_p_Data)
        {
            free(_p_Data);
            _p_Data = NULL;
        }
    }

    int m,n;

    T* _p_Data;

};

class IMatrix
{
public:
    virtual ~IMatrix() {};

    virtual double dotProduct(std::vector<double> p1, 
                                std::vector<double> p2,
                                int n) = 0;

    virtual double MatrixProduct() = 0;
};

#endif