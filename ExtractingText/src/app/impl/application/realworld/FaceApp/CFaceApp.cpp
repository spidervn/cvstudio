#include "CFaceApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/face/facemark_train.hpp>

using namespace cv;
using namespace cv::face;
using namespace std;

CFaceApp::CFaceApp()
{}

CFaceApp::~CFaceApp()
{}

int CFaceApp::run(int argc, char const* argv[])
{
    return ex02(argv[1]);
    return 0;
}

int CFaceApp::ex01(const char* file)
{
    Mat img;
    Mat frame;

    // img = imread(file, IMREAD_COLOR);
    // frame = Mat::zeros(img.size(), img.type());

    // Ptr<Facemark> facemark = createFacemarkLBF();

    // std::vector<Rect> faces;
    // std::vector<std::vector<Point2f> > landmarks;
    // facemark->getFaces(img, faces);
    // facemark->fit(img, faces, landmarks);

    // for(int j=0;j<faces.size();j++){
    //     face::drawFacemarks(frame, landmarks[j], Scalar(0,0,255));
    // }

    // imshow("img", img);
    // imshow("frame", frame);

    // waitKey();
    return 0;
}

int CFaceApp::ex02(const char* file)
{
    Mat img;
    Mat frame;

    frame = imread(file, IMREAD_COLOR);
    std::vector<cv::Rect> faces;
    CParams params("haarcascade_frontalface_alt.xml");
    cv::face::getFaces(frame, faces, &params);
    for(int j=0;j<faces.size();j++){
        cv::rectangle(frame, faces[j], cv::Scalar(255,0,255));
    }
    cv::imshow("detection", frame);

    waitKey();
    return 0;
}