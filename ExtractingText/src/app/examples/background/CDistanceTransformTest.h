#ifndef EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CDISTANCETRANSFORMTEST_H_
#define EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CDISTANCETRANSFORMTEST_H_

class CDistanceTransformTest
{
private:
    /* data */
public:
    CDistanceTransformTest(/* args */);
    ~CDistanceTransformTest();

    void test_1D();
    void bruteForce();

    double function_f(double a);
};

#endif