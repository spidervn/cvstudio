#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "app/impl/application/CSobelApp.h"
#include "app/impl/application/CRemappingApp.h"
#include "app/impl/application/CAffineTransform.h"

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    printf("Extracting text data\r\n");
    
    // if (argc <= 1)
    // {
    //     printf("Usage: %s <<image_file>>\r\n", argv[0]);
    //     return 0;
    // }
    // IApplication* p_App = new CSobelApp();
    // IApplication* p_App = new CRemappingApp();
    IApplication* p_App = new CAffineTransform();
    int n_Ret = p_App->run(argc, argv);
    delete p_App;

    return n_Ret;

    cv::Mat img;
    cv::Mat dst;
    img = cv::imread(argv[1], IMREAD_COLOR);
    
    cvtColor(img, dst, COLOR_BGR2GRAY);

    cv::namedWindow("Win");
    cv::imshow("Win", dst);

    waitKey(0);
    return 0;
}