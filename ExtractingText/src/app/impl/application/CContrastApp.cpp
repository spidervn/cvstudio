#include "CContrastApp.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CContrastApp::CContrastApp()
{

}

CContrastApp::~CContrastApp()
{

}

int CContrastApp::run(int argc, char const *argv[])
{
    printf("contrast <<image>>\r\n");
    Mat image = imread(argv[1]);
    
    if(image.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    Mat new_image = Mat::zeros(image.size(), image.type());

    double alpha = 1.0; /*< Simple contrast control */
    int beta = 0;       /*< Simple brightness control */
    cout << " Basic Linear Transforms " << endl;
    cout << "-------------------------" << endl;
    cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
    cout << "* Enter the beta value [0-100]: ";    cin >> beta;
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    imshow("Original Image", image);
    imshow("New Image", new_image);
    waitKey();
    return 0;
}