#ifndef EXTRACTTEXT_APP_IMPL_BACKGROUND_NEURAL_NETWORK_CFUNDAMENTALCNN_H_
#define EXTRACTTEXT_APP_IMPL_BACKGROUND_NEURAL_NETWORK_CFUNDAMENTALCNN_H_

/* Based from Stanford */
class CFundamentalCNN
{
private:
    /* data */
public:
    CFundamentalCNN(/* args */);
    virtual ~CFundamentalCNN();

    int linearClassfier();
    double softMax(const vector<double>& s, int k);
};

#endif