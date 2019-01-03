#include "CSVM.h"

CSVM::~CSVM()
{}

int CSVM::gradient_descent(int dimension_ofX, std::vector<VECTOR> v_x, std::vector<double> v_y, std::vector<double> v_theta)
{
    v_theta.reserve(dimension_ofX + 1);
    v_theta.clear();
    double alpha = 1;
    double arr_theta_new[100];

    // Initial value
    for(int i = 0; i < v_theta.size(); i++)
    {
        v_theta.push_back(1);
        // v_theta[i] = 1;
    }

    // Gradient descent
    // Repeat until convergence
    double sum;
    for (int i=0;i<1000;i++)
    {
        for (int l=0; l<dimension_ofX + 1; l++)
        {
            // 
            // ( y[j] - (v_x[j] * h(x[j]) ) * x[j]
            // 
            // (y[j] - h(x[j])) * x[i][j]
        
            arr_theta_new[l] = v_theta[l];
            
            // Scan every
            for (int k=0;k<v_x.size();k++)
            {
                double h_vxk = v_theta[0];
                for (int kk=1;kk<dimension_ofX+1;kk++)
                {
                    h_vxk += v_theta[kk] * v_x[k][kk-1];
                }

                arr_theta_new[i] += alpha*(v_y[k] - h_vxk) * v_x[k][l];
            }
        }

        for (int l=0; l<dimension_ofX + 1; l++)
        {
            v_theta[l] = arr_theta_new[l];
        }
    }

    return 0;
}