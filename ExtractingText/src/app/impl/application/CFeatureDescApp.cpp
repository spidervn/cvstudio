#include "CFeatureDescApp.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
// #include <opencv2/features2d.hpp>
#include <iostream>

using namespace std;

CFeatureDescApp::CFeatureDescApp(/* args */)
{
}

CFeatureDescApp::~CFeatureDescApp()
{
}

#ifdef HAVE_OPENCV_XFEATURES2D
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
int CFeatureDescApp::run(int argc, char const *argv[])
{

    const char* keys =
        "{ help h |                          | Print help message. }"
        "{ input1 | ../data/box.png          | Path to input image 1. }"
        "{ input2 | ../data/box_in_scene.png | Path to input image 2. }";

    CommandLineParser parser( argc, argv, keys );
    Mat img1 = imread( parser.get<String>("input1"), IMREAD_GRAYSCALE );
    Mat img2 = imread( parser.get<String>("input2"), IMREAD_GRAYSCALE );
    if ( img1.empty() || img2.empty() )
    { 
        cout << "Could not open or find the image!\n" << endl;
        parser.printMessage();
        return -1;
    }

    int minHessian = 400;
    Ptr<SURF> detector = SURF::create( minHessian );
    std::vector<KeyPoint> keypoints1, keypoints2;

    Mat descriptors1, descriptors2;
    detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1 );
    detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2 );

    // -- Step2: Matching descriptor vectors with a brute force matcher
    // 
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector<DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches);

    // Draw matches
    Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);

    // Show detected matches
    imshow("Matches", img_matches);
    waitKey();
    return 0;
}
#else
int CFeatureDescApp::run(int argc, char const *argv[])
{ 
    std::cout << "This tutorial code needs the xfeatures2d contrib module to be run." << std::endl;
    return 0;
}
#endif