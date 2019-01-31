#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "app/impl/application/CSobelApp.h"
#include "app/impl/application/CRemappingApp.h"
#include "app/impl/application/CAffineTransform.h"
#include "app/impl/application/CLaplaceApp.h"
#include "app/impl/application/CSVMApp.h"
#include "app/impl/application/CFourierApp.h"
#include "app/impl/application/CHistogramEqApp.h"
#include "app/impl/application/CFeatureDetectApp.h"
#include "app/impl/application/CHarrisCornerApp.h"
#include "app/impl/cv/CCVCore.h"

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    printf("Extracting text data\r\n");
    srand(time(NULL));

    // if (argc <= 1)
    // {
    //     printf("Usage: %s <<image_file>>\r\n", argv[0]);
    //     return 0;
    // }
    // IApplication* p_App = new CSobelApp();
    // IApplication* p_App = new CRemappingApp();
    // IApplication* p_App = new CAffineTransform();
    // IApplication* p_App = new CLaplaceApp();
    // IApplication* p_App = new CSVMApp();
    // int n_Ret = p_App->run(argc, argv);
    // IApplication* p_App = new CFourierApp();
    // IApplication* p_App = new CHistogramEqApp();
    // IApplication* p_App = new CFeatureDetectApp();

    /*
    IApplication* p_App = new CHarrisCornerApp();
    int n_Ret;
    n_Ret = p_App->run(argc, argv); // = ((CSVMApp*)p_App)->run4();
    delete p_App;
    */

    Mat img;
    img = imread("/home/jcm/Pictures/opencv/donald-trump.jpg", IMREAD_COLOR);

    // namedWindow("A", WINDOW_AUTOSIZE);
    // imshow("A", img);
    // waitKey();

    ICVCore* pCv = new CCVCore();
    pCv->HarrisCorner(img);
    delete pCv;

    return 0;

    /*
    cv::Mat img;
    cv::Mat dst;
    img = cv::imread(argv[1], IMREAD_COLOR);
    
    cvtColor(img, dst, COLOR_BGR2GRAY);
    cv::namedWindow("Win");
    cv::imshow("Win", dst);
    waitKey(0);
    return 0;
    */
}