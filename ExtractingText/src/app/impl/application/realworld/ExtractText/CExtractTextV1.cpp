#include "CExtractTextV1.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
using namespace std;
using namespace cv;

CExtractTextV1::CExtractTextV1()
{

}

CExtractTextV1::~CExtractTextV1()
{

}

int CExtractTextV1::run(int argc, char const* argv[])
{
    cv::Mat img;
    cv::Mat edge;
    cv::Mat cdst;

    // 
    //@Labelling the Image
    // 
    img = imread(argv[1], IMREAD_GRAYSCALE);

    if (img.empty())
    {
        printf("Fail to read\r\n");
        return -1;
    }

    Canny(img, edge, 50, 200, 3);
    cvtColor(edge, cdst, COLOR_GRAY2BGR);

    // 
    // Detect lines
    // 
    vector<Vec2f> vline;
    HoughLines(edge, vline, 1, CV_PI/180, 15, 0, 0);
    printf("Detected %d lines\r\n", vline.size());

    for (size_t i=0; i<vline.size();++i)
    {
        float rho = vline[i][0];
        float theta = vline[i][1];

        Point pt1, pt2;
        double a,b,x0,y0;

        a = cos(theta);
        b = sin(theta);
        x0 = a*rho;
        y0 = b*rho;

        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));

        line(cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }

    imshow("img", img);
    imshow("edge", edge);
    imshow("cdst", cdst);

    waitKey();
    return 0;
}