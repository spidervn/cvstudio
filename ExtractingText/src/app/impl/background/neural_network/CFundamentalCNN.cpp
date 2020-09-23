#include "CFundamentalCNN.h"
#include <vector>
#include <math.h>
using namespace std;

CFundamentalCNN::CFundamentalCNN(/* args */)
{
}

CFundamentalCNN::~CFundamentalCNN()
{
}

int CFundamentalCNN::linearClassfier()
{
    // 
    // Kind of where we stopped off that 
    // 

    double x;   // m x n
    double W;   // n x 1
    double f_xW = W * x;    // The score

    // Dataset of examples
    vector<double> vX;  // n images
    vector<int> vY;     // n labels

    // Loss function = How good current classifier is.
    // Loss over dataset
    double L;   // 1/N * sum{i}L[i](f(x[i],W), y[i])

    // Multi-class SVM loss
    double L_mc_svm;    // L[i] = Sum{j != y[i]} max(0, s[j] - s[y[i]] + 1)
                        // Where s = f(x[i],W)

    // 
    // Regularization: expression preferences
    // w[1]T*x = w[2]T*x = 1
    //      R(W) = 
    
    // Softmax classifier
    // F=3; S=2;

    return 0;
}

//
// Calculate softMax function
//      softmax(s,k) = e^(s[k]) / (sum{i}e^(s[i]))
//
double CFundamentalCNN::softMax(const vector<double>& s, int k)
{
    double d;
    double U, D;

    int n = s.size();

    U = exp(s[k]);
    D = 0;
    for (int i=0;i<n;++i)
    {
        D += exp(s[i]);
    }

    return U/D;
}

int CFundamentalCNN::maxPooling(int w1, int h1, int d1, 
                        int f, int stride,
                        int& w2, int& h2, int& d2)
{
    // 
    // Down sampling
    // 
    w2 = (w1-f)/stride + 1;
    h2 = (h1-f)/stride + 1;
    d2 = d1;
    return 0;
}