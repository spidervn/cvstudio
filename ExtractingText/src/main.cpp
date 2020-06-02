#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "app/impl/general/CConsole.h"
#include "app/impl/application/CSmoothImgApp.h"
#include "app/impl/application/CSobelApp.h"
#include "app/impl/application/CRemappingApp.h"
#include "app/impl/application/CAffineTransform.h"
#include "app/impl/application/CLaplaceApp.h"
#include "app/impl/application/CSVMApp.h"
#include "app/impl/application/CFourierApp.h"
#include "app/impl/application/CHistogramEqApp.h"
#include "app/impl/application/CHistogramCalcApp.h"
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
#include "app/impl/application/CColorizeApp.h"
#include "app/impl/application/CPoultryMonitorApp.h"
#include "app/impl/application/poultry/CPinaclePoutryApp.h"
#include "app/impl/application/CTemplateMatchingApp.h"
#include "app/impl/application/CCannyEdgeApp.h"
#include "app/impl/application/CHitOrMissApp.h"
#include "app/impl/application/CBackprojectApp.h"
#include "app/impl/application/CBackprojectApp2.h"
#include "app/impl/application/CAnisotropicSegmentation.h"
#include "app/impl/application/CContrastApp.h"
#include "app/impl/application/CHoughLineApp.h"
#include "app/impl/application/CHoughCircleApp.h"
#include "app/impl/application/CContoursApp.h"
#include "app/impl/application/CPencilingApp.h"
#include "app/impl/application/poultry/CParametricTemplateVectorApp.h"
#include "app/impl/application/poultry/CManualFundamentalApp.h"
#include "app/impl/application/background/CProbabilityApp.h"
#include "app/impl/application/CSVMNonLinearApp.h"
#include "app/impl/application/CPCAApp.h"
#include "app/impl/application/calculus/CCalculusApp.h"
#include "app/examples/background/CDistanceTransformTest.h"
#include "app/examples/background/CHoughLineTest.h"
#include "app/examples/background/CVTKTest.h"

#include "app/impl/application/realworld/FaceApp/CFaceApp.h"
#include "app/impl/application/realworld/FaceApp/CHelenParser.h"
#include "app/impl/application/realworld/ExtractText/CExtractTextV1.h"
#include "app/impl/application/realworld/Camera/CCameraTechApp.h"

#include "app/examples/background/CSlamTest.h"
#include "app/impl/cv/CCVCore.h"

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    printf("Extracting text data\r\n");
    srand(time(NULL));

    cout << "OpenCV version : " << CV_VERSION << endl;
    cout << "Major version : " << CV_MAJOR_VERSION << endl;
    cout << "Minor version : " << CV_MINOR_VERSION << endl;
    cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

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
    // IApplication* p_App = new CHistogramCalcApp();
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
    // IApplication* p_App = new CPyramidManualApp();
    // IApplication* p_App = new CColorizeApp();
    // IApplication* p_App = new CPoultryMonitorApp();
    // IApplication* p_App = new CPinaclePoutryApp();
    // IApplication* p_App = new CTemplateMatchingApp();
    // IApplication* p_App = new CCannyEdgeApp();
    // IApplication* p_App = new CHitOrMissApp();
    // IApplication* p_App = new CBackprojectApp();
    // IApplication* p_App = new CBackprojectApp2();
    // IApplication* p_App = new CAnisotropicSegmentation();
    // IApplication* p_App = new CContrastApp();
    // IApplicationPtr p_App = CHoughLineAppPtrNew();
    // IApplication* p_App = new CHoughCircleApp();
    // IApplication* p_App = new CContoursApp();
    // IApplication* p_App = new CParametricTemplateVectorApp();
    // IApplicationPtr p_App = CManualFundamentalAppPtrNew();
    // IApplication* p_App = new CPencilingApp();
    // IApplication* p_App = new CProbabilityApp();
    // IApplicationPtr p_App = CSVMNonLinearAppPtrNew;
    // IApplication* p_App = new CCalculusApp();
    // IApplication* p_App = new CSlamTest();
    // IApplication* p_App = new CSmoothImgApp();
    // IApplicationPtr p_App = CHoughLineTestPtrNew();
    // IApplicationPtr p_App = CExtractTextV1PtrNew();
    // IApplicationPtr p_App = CVTKTestPtrNew;
    // IApplicationPtr p_App = CFaceAppPtrNew();
    // IApplicationPtr p_App = CHelenParserPtrNew();
    // IApplicationPtr p_App = CCameraTechAppPtrNew();

    IApplicationPtr p_App = CCameraTechAppPtrNew();    
    int n_Ret = p_App->run(argc, argv);

    /*
        int p = 6089;
        std::vector<int> v;
        ICVCorePtr ccp;
        ccp = CCVCorePtrNew;
        ccp->lehmerRNG(p, 100, 7, v);
        CConsole::print<int>(v);
     */
    // 
    // CDistanceTransformTest tt;
    // int n_Ret;
    // tt.test_1D();
    // tt.bruteForce();
    // tt.test_2D("/home/jcm/Pictures/opencv/donald-trump.jpg");
    // 

    // delete p_App;
    return 0;
}
