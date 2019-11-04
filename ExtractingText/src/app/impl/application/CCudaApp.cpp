#include "CCudaApp.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

/*
template<typename T>
thrust::permutation_iterator<thrust::device_ptr<T>, thrust::transform_iterator<step_functor<T>, thrust::counting_iterator<int>>>  GpuMatBeginItr(cv::cuda::GpuMat mat, int channel = 0)
{
    if (channel == -1)
    {
        mat = mat.reshape(1);
        channel = 0;
    }
    CV_Assert(mat.depth() == cv::DataType<T>::depth);
    CV_Assert(channel < mat.channels());
    return thrust::make_permutation_iterator(thrust::device_pointer_cast(mat.ptr<T>(0) + channel),
        thrust::make_transform_iterator(thrust::make_counting_iterator(0), step_functor<T>(mat.cols, mat.step / sizeof(T), mat.channels())));
}
*/

CCudaApp::CCudaApp(/* args */)
{
}

CCudaApp::~CCudaApp()
{
}

int CCudaApp::run(int argc, char const *argv[])
{

    return 0;
}