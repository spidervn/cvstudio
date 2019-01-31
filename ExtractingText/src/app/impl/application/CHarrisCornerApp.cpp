#include "CHarrisCornerApp.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CHarrisCornerApp::CHarrisCornerApp()
{
    source_window = "Source Image";
    corners_window = "Corners detected";    
}

CHarrisCornerApp::~CHarrisCornerApp()
{}

int CHarrisCornerApp::run(int argc, char const *argv[])
{
    // const char* source_window = "Source Image";
    // const char* corners_window = "Corners detected";

    thresh = 200;
    max_thresh = 255;

    CommandLineParser parser( argc, argv, "{@input | ../data/building.jpg | input image}" );
    src = imread( parser.get<String>( "@input" ) );

    if ( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY );

    namedWindow( source_window );
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, onChangeTrack, this );
    imshow( source_window, src);

    onChangeTrack(0, (void*)this);
    waitKey();

    return 0;
}

void CHarrisCornerApp::cornerHarris_demo(int, void* pData)
{
    // const char* source_window = "Source Image";
    // const char* corners_window = "Corners detected";
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    Mat dst = Mat::zeros( src.size(), CV_32FC1 );
    cornerHarris( src_gray, dst, blockSize, apertureSize, k );
    Mat dst_norm, dst_norm_scaled;
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );
    for( int i = 0; i < dst_norm.rows ; i++ )
    {
        for( int j = 0; j < dst_norm.cols; j++ )
        {
            if( (int) dst_norm.at<float>(i,j) > thresh )
            {
                circle( dst_norm_scaled, Point(j,i), 5,  Scalar(0), 2, 8, 0 );
            }
        }
    }
    namedWindow( corners_window );
    imshow( corners_window, dst_norm_scaled );
}

void CHarrisCornerApp::onChangeTrack(int nData, void* pData)
{
    CHarrisCornerApp* p_App = (CHarrisCornerApp*)pData;

    if (p_App != NULL)
    {
        p_App->cornerHarris_demo(nData, NULL);
    }
}