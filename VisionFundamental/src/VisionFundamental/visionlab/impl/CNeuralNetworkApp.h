#ifndef VSIONFUND_VISIONLAB_IMPL_CNEURALNETWORKAPP_H_
#define VSIONFUND_VISIONLAB_IMPL_CNEURALNETWORKAPP_H_

#include "visionlab/interface/IApplication.h"

class CNeuralNetworkApp: public IApplication
{
private:
    /* data */
public:
    CNeuralNetworkApp(/* args */);
    ~CNeuralNetworkApp();

    int run(int argc, char const* argv[]);
};

#endif