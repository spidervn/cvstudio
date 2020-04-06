#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_IMATRIX_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_IMATRIX_H_

#include <opencv2/core.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

template <typename T>
class Matrix
{
public:

    Matrix()
    {
        m = 0;
        n = 0;

        _p_Data = NULL;
    }

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
   
    void operator=(const Matrix<T>& mtx)
    {
        __freeMatrix();
        
        m = mtx.m;
        n = mtx.n;

        _p_Data = malloc(m*n*sizeof(T));
        memcpy(_p_Data, mtx._p_Data, m*n*sizeof(T));
    }

    T get(int y, int x)
    {
        return _p_Data[y*m + x];
    }

    void set(int y, int x, T t)
    {
        _p_Data[y*m + x] = t;
    }

    int rows() { return m; }
    int cols() { return n; }

    T* rows(int row_idx) { return &_p_Data[row_idx * m]; }  // Start position of rows row_idx
    T* cols(int col_idx) { return &_p_Data[col_idx]; }      // Start position of column col_idx

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
    
    template <typename IteratorVectorA, typename IteratorVectorB>
    static double dotProduct(IteratorVectorA p1, 
                                IteratorVectorB p2,
                                int n,
                                int step_v1=1,
                                int step_v2=1)
    {
        int i =0;
        double ret = 0;
        while ( i < n) 
        {
            ret += (*p1) * (*p2);
            p1+=step_v1;
            p2+=step_v2;
            i++;
        }

        return ret;
    }

    virtual int  MatrixProduct(Matrix<double> m1, Matrix<double> m2, Matrix<double>& m_out) = 0;

    virtual double det(Matrix<double> m) = 0;  // Det of a Matrix?
    
    virtual double det(const cv::Mat& m) = 0;

};

#endif