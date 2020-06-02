#include "CCameraTechApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
using namespace cv;
using namespace std;

CCameraTechApp::CCameraTechApp()
{
 
}

CCameraTechApp::~CCameraTechApp()
{

}

int CCameraTechApp::run(int argc, char const* argv[])
{
    PinholeCoefficient myntEye;

    // There is no distortion after stereo rectification
    myntEye.k1 = 0.0;
    myntEye.k2 = 0.0;

    myntEye.p1 = 0.0;
    myntEye.p2 = 0.0;

    myntEye.k3 = 0.0;


    // Position in Image Pixel
    double u;
    double v;

    cv::Mat m = (Mat_<double>(3,1) << u, v, 1.0);   // Homogenneous coordinates

    // Position in World coordinates (3D)
    double xw;
    double yw;
    double zw;
    cv::Mat mw = (Mat_<double>(4,1) << xw, yw, zw, 1.0);

    // Projecting world coordinates to pixel coordinates
    double fx, fy, cx, cy;

    std::vector<Point3d> vP3;
    std::vector<Point2d> vP2;

    fx = 369.855;
    fy = 369.855;
    cx = 514.657;
    cy = 241.241;

    cv::Mat cameraMatrix = (Mat_<double>(3,3) << 
            fx, 0, cx,
            0, fy, cy,
            0, 0, 1);

    cv::Mat rvec;
    cv::Mat tvec;

    vP3.push_back(cv::Point3d(1.0, 1.0, 1.0));
    vP2.push_back(cv::Point2d(2.0, 2.0));

    cv::solvePnP(
                vP3,
                vP2,
                cameraMatrix,
                cv::Mat(),
                rvec,
                tvec);

    cout << "Output of PnP " << rvec << "; tvec= " << tvec << endl;
    return 0;
}