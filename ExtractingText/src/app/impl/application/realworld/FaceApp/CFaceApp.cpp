#include "CFaceApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;
using namespace std;

CFaceApp::CFaceApp()
{}

CFaceApp::~CFaceApp()
{}

int CFaceApp::run(int argc, char const* argv[])
{
    Mat img;
    Mat frame;

    img = imread(argv[1], IMREAD_COLOR);
    frame = Mat::zero(img.size(), img.type());


    std::vector<Rect> faces;
    std::vector<std::vector<Point2f> > landmarks;
    facemark->getFaces(img, faces);
    facemark->fit(img, faces, landmarks);

    for(int j=0;j<rects.size();j++){
        face::drawFacemarks(frame, landmarks[j], Scalar(0,0,255));
    }

    imshow("img", img);
    imshow("frame", frame);

    waitKey();
    return 0;
}