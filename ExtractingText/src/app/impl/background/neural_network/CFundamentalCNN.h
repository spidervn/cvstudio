#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_NEURAL_NETWORK_CFUNDAMENTALCNN_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_NEURAL_NETWORK_CFUNDAMENTALCNN_H_

#include <vector>

/* Based from Stanford */
class CFundamentalCNN
{
private:
    /* data */
public:
    CFundamentalCNN(/* args */);
    virtual ~CFundamentalCNN();

    int linearClassfier();
    double softMax(const std::vector<double>& s, int k);

    int maxPooling(int w1, int h1, int d1, 
                        int f, int stride,
                        int& w2, int& h2, int& d2);
};

#endif