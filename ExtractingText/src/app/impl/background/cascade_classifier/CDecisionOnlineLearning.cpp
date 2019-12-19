#include "CDecisionOnlineLearning.h"
#include <vector>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

CDecisionOnlineLearning::CDecisionOnlineLearning(/* args */)
{
}

CDecisionOnlineLearning::~CDecisionOnlineLearning()
{
}

// General concepts 
int CDecisionOnlineLearning::board()
{
    //@Gambler
    int MAX_N = 100;
    int TIME = 100;
    int NAgent; // Number of agent that @Gambler want let 
    int T;      // Total time
    
    int aAgent[TIME][MAX_N];      // Skill rate of agent[i]
    int aLoss[TIME][MAX_N];       // Loss: affected by environment

    int wage;
    
    int netLoss = 0;
    int L_A = 0;        // totalCummulativeLoss = 0;
    int L[TIME][MAX_N]; // Loss[i]
    // On-line allocation model

    NAgent = 1;
    T = 1;


    // Total Cummulative Loss
    for (int t=0; t<T; ++t)
    {
        int ptlt = 0;
        for (int i=0; i<NAgent; ++i)
        {
            ptlt += aAgent[t][i] * aLoss[t][i];
        }

        L_A += ptlt;
    }

    // Online allocation model
    Mat p[TIME];    // Agent distribution from time;
    Mat l[TIME];    // environment loss 

    (p[0]*l[0]);
    


    return 0;
}