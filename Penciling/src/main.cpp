#include <stdio.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    cv::Mat img;
    cv::Mat imgGray;
    cv::Mat img_NoNoise;
    cv::Mat grad_x;
    cv::Mat grad_y;
    cv::Mat abs_grad_x;
    cv::Mat abs_grad_y;
    cv::Mat grad;
    cv::Mat invertgrad;
    cv::Mat img_Bil;
    int ksize = -1; // parser.get<int>("ksize");
    int scale = 1; //parser.get<int>("scale");
    int delta = 0; // parser.get<int>("delta");
    int ddepth = CV_16S;

    const char* szImageToPencil = "Image2Pencil";
    const char* szBilateral = "Bilateral";

    img = imread(argv[1], IMREAD_COLOR);

    GaussianBlur(img, img_NoNoise, Size(3,3), 0, 0, BORDER_DEFAULT);
    bilateralFilter(img, img_Bil, 40, 60, 60);
    cvtColor(img_NoNoise, imgGray, COLOR_BGR2GRAY);
    
    Sobel(imgGray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
    Sobel(imgGray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    invertgrad = (255-grad);
    namedWindow(szImageToPencil, WINDOW_AUTOSIZE);
    namedWindow(szBilateral, WINDOW_AUTOSIZE);

    imshow(szImageToPencil, invertgrad);
    imshow(szBilateral, img_Bil);

    imwrite("./out.jpg", invertgrad);
    imwrite("./out2.jpg", img_Bil);
    waitKey(0);
    return 0;
}
