#include "CImageSegmentationApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

CImageSegmentationApp::CImageSegmentationApp(/* args */)
{
}

CImageSegmentationApp::~CImageSegmentationApp()
{
}

int CImageSegmentationApp::run(int argc, char const *argv[])
{
    CommandLineParser parser( argc, argv, "{@input | ../data/cards.png | input image}" );
    Mat src = imread(parser.get<String>("@input"));

    if (src.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;      
    }

    // Show source image
    imshow("Source Image", src);

    // While background => black background
    for ( int i = 0; i < src.rows; i++ ) {
        for ( int j = 0; j < src.cols; j++ ) {
            if ( src.at<Vec3b>(i, j) == Vec3b(255,255,255) )
            {
                src.at<Vec3b>(i, j)[0] = 0;
                src.at<Vec3b>(i, j)[1] = 0;
                src.at<Vec3b>(i, j)[2] = 0;
            }
        }
    }

    // Show output image
    imshow("Black BG", src);

    // Create a kernel that we will use to sharpen our image
    Mat kernel = (Mat_<float>(3,3) << 
            1, 1, 1,
            1, -8, 1,
            1, 1, 1);   // an appromixation of second derivative a quite strong kernel

    Mat imgLaplacian;
    Mat sharp;
    Mat imgResult;

    filter2D(src, imgLaplacian, CV_32F, kernel);
    src.convertTo(sharp, CV_32F);

    imgResult = sharp - imgLaplacian;
    //Black to gray scale
    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
    imshow("New Sharped Image", imgResult);

    // Create binary image from source image
    Mat bw;
    cvtColor(imgResult, bw, COLOR_BGR2GRAY);
    threshold(bw, bw, 40, 255, THRESH_BINARY | THRESH_OTSU);
    imshow("Binary Image", bw);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(bw, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);
    imshow("Distance transform image", dist);
    threshold(dist, dist, 0.4, 1.0, THRESH_BINARY);

    // Dilate a bit the dist-image
    Mat kernel1 = Mat::ones(3, 3, CV_8U);
    dilate(dist, dist, kernel1);
    imshow("Peaks", dist);

    //
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find total markers
    vector<vector<Point> > contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Create the marker image for the watershed algorihm
    Mat markers = Mat::zeros(dist.size(), CV_32S);

    // Draw the foreground markers
    for (size_t i=0; i<contours.size(); ++i)
    {
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i)+1), -1);
    }

    // Draw the background marker
    circle(markers, Point(5, 5), 3, Scalar(255), -1);
    imshow("Markers", markers * 1000);

    // Performs the watershed
    watershed(imgResult, markers);

    Mat mark;
    markers.convertTo(mark, CV_8U);
    bitwise_not(mark, mark);

    // Generate random colors
    vector<Vec3b> colors;
    for (size_t i=0; i< contours.size(); i++)
    {
        int b = theRNG().uniform(0, 256);
        int g = theRNG().uniform(0, 256);
        int r = theRNG().uniform(0, 256);

        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    // Find labeled objects with random colors
    for (int i=0; i<markers.rows; i++)
    {
        for (int j=0; j<markers.cols; j++)
        {
            int index = markers.at<int>(i,j);

            if (index >0 && index <= static_cast<int>(contours.size()))
            {
                dst.at<Vec3b>(i,j) = colors[index - 1];
            }
        }
    }

    // Visualize the final results
    imshow("Final result", dst);

    waitKey();
    return 0;
}