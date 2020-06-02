#include "CHelenParser.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

/*
 * This Application read and parse the annotations text file of Helen dataset.
 *      - Get Filename
 *      - 
 * Note:
 *  Helen dataset is mentioned in official opencv's (verison 4.3.0) tutorial (Training face landmark detector)
 */

CHelenParser::CHelenParser()
{}

CHelenParser::~CHelenParser()
{}

int CHelenParser::run(int argc, char const* argv[])
{
    // 
    // Annotation text file
    // 
    string file_annotation;
    ifstream f;
    cv::Mat img;

    f.open(argv[1]);
    std::vector<cv::Point2f> vanno;

    if (!f.is_open())
    {
        printf("Invalid file\r\n");
        return -1;
    }

    f >> file_annotation;

    printf("File=%s\r\n", file_annotation.c_str());
    int i = 0;

    while (!f.eof())
    {
        double x;
        double y;
        char comma;
        bool bread = true;
        bread = bread && (f >> x);
        bread = bread &&(f >> comma);
        bread = bread && (f >> y);

        if (bread)
        {
            printf("(x,y)=(%f,%f)\r\n", x, y);
            i++;

            vanno.push_back(cv::Point2f(x,y));
        }
    }

    f.close();
    printf("Finish (count=%d)\r\n", i);

    img = imread(file_annotation + ".jpg", IMREAD_COLOR);
    for (int i=0; i<vanno.size();++i)
    {
        cv::circle(
            img,
            vanno[i],
            2,
            Scalar(255,0,0));
    }
    
    imshow("img", img);
    waitKey();
    return 0;
}
