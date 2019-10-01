#include "CContoursApp.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

CContoursApp::CContoursApp(): rng(12345), thresh(100)
{
    
}

CContoursApp::~CContoursApp()
{}

int CContoursApp::run(int argc, char const *argv[])
{
    CommandLineParser parser( argc, argv, "{@input | ../data/HappyFish.jpg | input image}" );
    src = imread( parser.get<String>( "@input" ) );
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }
    printf("xxx\r\n");
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );
    const int max_thresh = 255;
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, Callback, (void*)this);
    Callback( 0, (void*)this);

    waitKey();
    return 0;
}

void CContoursApp::contourRc(const std::vector<cv::Point>& v, cv::Rect& r)
{
    r = Rect(-1,-1,-1,-1);
    
    //
    // Trick: use width & height to store (right, bottom)
    //
    for (int i=0; i<v.size(); ++i)
    {
        if (r.x == -1)
        {
            r.x = v[i].x;
        }
        else if (v[i].x < r.x)
        {
            r.x = v[i].x;
        }
        if (r.width == -1)
        {
            r.width = v[i].x;
        }
        else if (r.width < v[i].x)
        {
            r.width = v[i].x;
        }            

        if (r.y == -1)
        {
            r.y = v[i].y;
        }
        else if (v[i].y < r.y)
        {
            r.y = v[i].y;
        }

        if (r.height == -1)
        {
            r.height = v[i].y;                
        }
        else if ( r.height < v[i].y)
        {
            r.height = v[i].y;
        }
    }

    // Un-trick
    r.width = r.width - r.x;
    r.height = r.height - r.y;
}

void CContoursApp::Callback(int,void* pData)
{
    if (pData != NULL)
    {
        CContoursApp* p_App = (CContoursApp*)pData;

        Mat canny_output;
        Canny( p_App->src_gray, canny_output, p_App->thresh, p_App->thresh*2 );
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
        Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Scalar color = Scalar( p_App->rng.uniform(0, 256), p_App->rng.uniform(0,256), p_App->rng.uniform(0,256) );
            drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
        }

        int area_low = 350;
        int area_hig = 550;
        for( size_t i = 0; i< contours.size(); i++ )
        {
            Rect rc;
            p_App->contourRc(contours[i], rc);

            if (rc.width > 0)
            {
                double ratio = (double)rc.height / (double)rc.width;
                int area = rc.width * rc.width;

                if (ratio >= 0.35 && ratio <= 1.9 && area >= area_low && area <= area_hig)
                {
                    rectangle(p_App->src, rc, Scalar(255,255,0));
                }
            }
        }
        imshow("Source", p_App->src);
        imshow( "Contours", drawing );
    }
}