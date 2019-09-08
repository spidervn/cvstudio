#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
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
#include "app/impl/application/CFeatureDescApp.h"
#include "app/impl/application/CHarrisCornerApp.h"
#include "app/impl/application/CShiTomasiApp.h"
#include "app/impl/application/COwnCornerDetectApp.h"
#include "app/impl/application/CCornerLocationSubpixelsApp.h"
#include "app/impl/application/CImageSegmentationApp.h"
#include "app/impl/application/CImgResizingApp.h"
#include "app/impl/application/CSobelManualApp.h"
#include "app/impl/application/CExtractTextApp.h"
#include "app/impl/application/CBanknoteStainedApp.h"
#include "app/impl/application/CPyramidManualApp.h"
#include "app/examples/background/CDistanceTransformTest.h"

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
    // IApplication* p_App = new CHarrisCornerApp();
    // IApplication* p_App = new CShiTomasiApp();
    // IApplication* p_App = new COwnCornerDetectApp();
    // IApplication* p_App = new CCornerLocationSubpixelsApp();
    // IApplication* p_App = new CFeatureDescApp();
    // IApplication* p_App = new CImageSegmentationApp();
    // IApplication* p_App = new CImgResizingApp();
    // IApplication* p_App = new CSobelManualApp();
    // IApplication* p_App = new CExtractTextApp();
    IApplication* p_App = new CPyramidManualApp();

    int n_Ret = p_App->run(argc, argv);

    // CDistanceTransformTest tt;
    // int n_Ret;
    //tt.test_1D();
    //tt.bruteForce();
    // tt.test_2D("/home/jcm/Pictures/opencv/donald-trump.jpg");

    delete p_App;
    return 0;
}