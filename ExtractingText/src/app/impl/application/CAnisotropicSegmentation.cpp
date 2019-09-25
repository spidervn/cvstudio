#include "CAnisotropicSegmentation.h"

using namespace cv;
using namespace std;

CAnisotropicSegmentation::CAnisotropicSegmentation(/* args */)
{
}

CAnisotropicSegmentation::~CAnisotropicSegmentation()
{
}

int CAnisotropicSegmentation::run(int argc, char const *argv[])
{
    printf("anisotropic_segmentation <<image>>\r\n");
    int W = 52;             // window size is WxW
    double C_Thr = 0.43;    // threshold for coherency
    int LowThr = 35;        // threshold1 for orientation, it ranges from 0 to 180
    int HighThr = 57;       // threshold2 for orientation, it ranges from 0 to 180

    Mat imgIn = imread(argv[1], IMREAD_GRAYSCALE);
    Mat imgCoherency, 
        imgOrientation;
    Mat imgCoherencyBin;
    Mat imgOrientationBin;
    Mat imgBin;
    
    calcGST(imgIn, imgCoherency, imgOrientation, W);
    inRange(imgOrientation, Scalar(LowThr), Scalar(HighThr), imgOrientationBin);

    imgBin = imgCoherencyBin & imgOrientationBin;

    normalize(imgCoherency, imgCoherency, 0, 255, NORM_MINMAX);
    normalize(imgOrientation, imgOrientation, 0, 255, NORM_MINMAX);

    imwrite("result.jpg", 0.5 * (imgIn + imgBin));
    imwrite("Coherency.jpg", imgCoherency);
    imwrite("Orientation.jpg", imgOrientation);
    return 0;
}

void CAnisotropicSegmentation::calcGST(const cv::Mat& inputImg, cv::Mat& imgCoherencyOut, cv::Mat& imgOrientationOut, int w)
{
    Mat img;
    inputImg.convertTo(img, CV_64F);
    // GST components calculation (start)
    // J =  (J11 J12; J12 J22) - GST
    Mat imgDiffX, imgDiffY, imgDiffXY;
    Sobel(img, imgDiffX, CV_64F, 1, 0, 3);
    Sobel(img, imgDiffY, CV_64F, 0, 1, 3);
    multiply(imgDiffX, imgDiffY, imgDiffXY);
    Mat imgDiffXX, imgDiffYY;
    multiply(imgDiffX, imgDiffX, imgDiffXX);
    multiply(imgDiffY, imgDiffY, imgDiffYY);
    Mat J11, J22, J12;      // J11, J22 and J12 are GST components
    boxFilter(imgDiffXX, J11, CV_64F, Size(w, w));
    boxFilter(imgDiffYY, J22, CV_64F, Size(w, w));
    boxFilter(imgDiffXY, J12, CV_64F, Size(w, w));
    // GST components calculation (stop)
    // eigenvalue calculation (start)
    // lambda1 = J11 + J22 + sqrt((J11-J22)^2 + 4*J12^2)
    // lambda2 = J11 + J22 - sqrt((J11-J22)^2 + 4*J12^2)
    Mat tmp1, tmp2, tmp3, tmp4;
    tmp1 = J11 + J22;
    tmp2 = J11 - J22;
    multiply(tmp2, tmp2, tmp2);
    multiply(J12, J12, tmp3);
    sqrt(tmp2 + 4.0 * tmp3, tmp4);
    Mat lambda1, lambda2;
    lambda1 = tmp1 + tmp4;      // biggest eigenvalue
    lambda2 = tmp1 - tmp4;      // smallest eigenvalue
    // eigenvalue calculation (stop)
    // Coherency calculation (start)
    // Coherency = (lambda1 - lambda2)/(lambda1 + lambda2)) - measure of anisotropism
    // Coherency is anisotropy degree (consistency of local orientation)
    divide(lambda1 - lambda2, lambda1 + lambda2, imgCoherencyOut);
    // Coherency calculation (stop)
    // orientation angle calculation (start)
    // tan(2*Alpha) = 2*J12/(J22 - J11)
    // Alpha = 0.5 atan2(2*J12/(J22 - J11))
    phase(J22 - J11, 2.0*J12, imgOrientationOut, true);
    imgOrientationOut = 0.5*imgOrientationOut;
    // orientation angle calculation (stop)
}
