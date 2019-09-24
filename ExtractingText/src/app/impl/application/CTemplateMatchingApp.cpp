#include "CTemplateMatchingApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "inih-master/INIReader.h"

using namespace cv;
using namespace std;

CTemplateMatchingApp::CTemplateMatchingApp()
{}

CTemplateMatchingApp::~CTemplateMatchingApp()
{}

int CTemplateMatchingApp::run(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("Usage: template_matching <<image>> <<template_image>>\r\n");
        return -1;
    }

    Mat img = imread(argv[1], IMREAD_COLOR);
    Mat templ = imread(argv[2], IMREAD_COLOR);
    Mat img_display;
    Mat mask;
    Mat result;

    bool use_mask = false;
    int match_method;
    int res_cols;
    int res_rows;

    bool method_accept_mask;

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    img.copyTo( img_display );

    int result_cols =  img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    
    result.create( result_rows, result_cols, CV_32FC1 );
    bool method_accepts_mask = 
                                (TM_SQDIFF == match_method || 
                                match_method == TM_CCORR_NORMED);

    use_mask = true;
    match_method = TM_SQDIFF;
    if (use_mask && method_accepts_mask)
    {
        matchTemplate( img, templ, result, match_method, mask);
    }
    else
    {
        matchTemplate(img, templ, result, match_method);
    }

    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
    {
        matchLoc = minLoc;
    }
    else
    {
        matchLoc = maxLoc;
    }

    rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
    imshow( "image display", img_display );
    imshow( "result window", result );

    waitKey();
    return 0;
}