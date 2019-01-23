#include "CFourierApp.h"

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using  namespace std;

CFourierApp::CFourierApp()
{}

CFourierApp::~CFourierApp()
{}

int CFourierApp::run(int argc, const char* argv[])
{
    if  (argc <  2)
    {
        printf("FourierTest <<image_file>>\r\n");
        return 0;
    }

    Mat I;
    Mat padded;                             // Expand input image to optimal size

    I =  imread(argv[1], IMREAD_GRAYSCALE);
    int  m = getOptimalDFTSize( I.rows );    
    int n = getOptimalDFTSize( I.cols );    // On the border add zero values

    copyMakeBorder(I, padded,  0, m - I.rows, 0, n - I.cols,  BORDER_CONSTANT, Scalar::all(0));

    Mat  planes[] = {  Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
    Mat  complexI;
    
    merge(planes, 2, complexI);
    dft(complexI, complexI);

    split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);
    
    Mat magI = planes[0];
    magI +=  Scalar::all(1);        // Switch to logarithmic scale
    log(magI, magI);

    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0,0,cx,cy));  
    Mat q1(magI, Rect(cx,0,cx,cy));
    Mat q2(magI, Rect(0,cy,cx,cy));
    Mat q3(magI, Rect(cx,cy,cx,cy));

    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, NORM_MINMAX);

    imshow("Input Image", I);
    imshow("Spectrum magnitude", magI);
    waitKey();

    return 0;
}