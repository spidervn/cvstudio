#include "CCalculusApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

CCalculusApp::CCalculusApp(/* args */)
{
}

CCalculusApp::~CCalculusApp()
{
}

int CCalculusApp::run(int, char const *[])
{
    int margin = 10;
    int MAX_IMGX = 1900;
    double R = 70;
    double split = 500;
    double dXMax = 0;

    std::vector<Point> vTraj;   // Trajectory
    vTraj.push_back(Point(0,0));

    printf("%f\r\n", sin(CV_PI/2));
    
    for (double st=1;st<=split;++st)
    {
        double alpha = st * CV_2PI / split;
        printf("alpha(%f)=%f;", st, alpha);

        double mysin = sin(alpha/2);
        printf("mysin=%f;", mysin);
        double x = 2*R*mysin*cos(alpha/2);
        double y = 2*R*mysin*mysin;

        printf("(x,y)=(%f,%f);", x, y);

        vTraj.push_back(Point(x,y));
    }

    cv::Mat img;
    // img = Mat::zeros(2*R + 2 * margin, std::min(vTraj[vTraj.size()-1].x, MAX_IMGX) + 2*margin, CV_8UC3);
    img = Mat::zeros(2*R + 2 * margin, 500, CV_8UC3);

    for (int st=0;st<=split;++st)
    {
        circle(img, 
            cv::Point(
                margin + vTraj[st].x,
                img.rows - margin - vTraj[st].y),
            1,
            Scalar(255,255,0));
    }

    printf("(%f,%f)\r\n", vTraj[vTraj.size()-1].x, vTraj[vTraj.size()-1].y);

    imshow("Chart", img);
    waitKey();
    return 0;
}