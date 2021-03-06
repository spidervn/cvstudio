#include "CFeatureDetectApp.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;
//using std::cout;
//using std::endl;

CFeatureDetectApp::CFeatureDetectApp()
{}

CFeatureDetectApp::~CFeatureDetectApp()
{}

int CFeatureDetectApp::run(int argc, char const *argv[])
{
    CommandLineParser parser( argc, argv, "{@input | ../data/box.png | input image}" );
    Mat src = imread( parser.get<String>( "@input" ), IMREAD_GRAYSCALE );
    if ( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    // --Step1: Detect the keypoints using SURF detector
    int minHessian = 400;
    Ptr<SURF> detector = SURF::create(minHessian);
    std::vector<KeyPoint> keypoints;
    detector->detect(src, keypoints);

    //-- Draw keypoints
    Mat img_keypoints;
    drawKeypoints(src, keypoints, img_keypoints);

    //-- Show detected (drawn) keypoints
    imshow("SURF Keypoints", img_keypoints);
    waitKey();

    return 0;
}