#include "CShiTomasiApp.h"

using namespace std;
using namespace cv;

CShiTomasiApp::CShiTomasiApp(/* args */)
{
}

CShiTomasiApp::~CShiTomasiApp()
{
}

int CShiTomasiApp::run(int argc, char const *argv[])
{
    const char* source_window = "Image";
    maxCorners = 23;
    maxTrackbar = 100;
    rng = RNG(12345);

    CommandLineParser parser( argc, argv, "{@input | ../data/pic3.png | input image}" );
    src = imread( parser.get<String>( "@input" ) );
    if( src.empty() )
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: ShiTomasi <Input image>" << endl;
        return -1;
    }

    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    namedWindow( source_window );
    createTrackbar( "Max corners:", source_window, &maxCorners, maxTrackbar, TrackbarCallback, (void*) this);
    imshow( source_window, src );
    goodFeaturesToTrack_Demo( 0, (void*)this );
    waitKey();

    return 0;
}

void CShiTomasiApp::goodFeaturesToTrack_Demo( int, void* )
{
    const char* source_window = "Image";

    maxCorners = MAX(maxCorners, 1);
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3, gradientSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    Mat copy = src.clone();
    goodFeaturesToTrack( src_gray,
                         corners,
                         maxCorners,
                         qualityLevel,
                         minDistance,
                         Mat(),
                         blockSize,
                         gradientSize,
                         useHarrisDetector,
                         k );
    cout << "** Number of corners detected: " << corners.size() << endl;
    int radius = 4;
    for( size_t i = 0; i < corners.size(); i++ )
    {
        circle( copy, corners[i], radius, Scalar(rng.uniform(0,255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED );
    }
    namedWindow( source_window );
    imshow( source_window, copy );
}

void CShiTomasiApp::TrackbarCallback( int nData, void* pData)
{
    if (pData != NULL)
    {
        CShiTomasiApp* pApp = (CShiTomasiApp*) pData;
        pApp->goodFeaturesToTrack_Demo(nData, pData);
    }
}