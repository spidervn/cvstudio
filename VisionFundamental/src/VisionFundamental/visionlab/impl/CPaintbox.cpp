#include "CPaintbox.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

CPaintbox::CPaintbox(/* args */)
{
}

CPaintbox::~CPaintbox()
{
}

int CPaintbox::paintBoard(cv::Mat img, cv::Rect rc)
{
    int step_x = rc.width /8;
    int step_y = rc.height/8;

    Scalar color[2] = {
        Scalar(0, 0, 0),
        Scalar(72, 255, 255)
    };

    for (int x=0; x<8; ++x)
    {
        for (int y=0; y<8; ++y)
        {
            Scalar c = color[(x+y) % 2];

            rectangle(img, Rect(rc.x + x*step_x, rc.y + y*step_y, step_x, step_y), c, 1, 8);
        }
    }

    return 0;
}