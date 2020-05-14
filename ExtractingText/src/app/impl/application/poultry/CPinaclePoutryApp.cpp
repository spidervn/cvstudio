#include "CPinaclePoutryApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "app/impl/general/CFileUtil.h"
#include "app/impl/cv/CCVCore.h"
#include "inih-master/INIReader.h"

using namespace cv;
using namespace std;

CPinaclePoutryApp::CPinaclePoutryApp(/* args */)
{
}

CPinaclePoutryApp::~CPinaclePoutryApp()
{
}

int CPinaclePoutryApp::run(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Pincale-poultry <<video>> <<config.ini>>\r\n");
        return -1;
    }

    // @Temp
    ICVCorePtr ccp1 = CCVCorePtrNew();
    /*
    cv::Mat src = imread(argv[1], IMREAD_COLOR);
    cv::Mat src_eql;
    cv::Mat src_buck;

    cvtColor(src, src, CV_BGR2GRAY);
    equalizeHist(src, src_eql);
    ccp1->bucketingColor(src_eql, 30, src_buck);

    imshow("src", src);
    imshow("equal", src_eql);
    imshow("buck", src_buck);

    waitKey();
    return 0;
    */

    /* 
     * 1) Step 
     *  - Change contrast by bucketing
     *  - finding contours
     *  - Seeking contours that appropirate chicken
     *  - Locate rectangle on screen
     */    

    int bucket;
    int broiler_low = 70*70;
    int broiler_hig = 90*90;
    int video_w;
    int video_h;
    int canny_thresh = 100;
    double broiler_rate_low = 0.45;
    double broiler_rate_hig = 0.7;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;    
    const char* szIni = argv[2];
    const char* szVideo = argv[1];

    const char* szWin = "Source";
    const char* szBuckwet = "High-contrast";
    const char* szHSL = "HSL";
    ICVCorePtr ccp = CCVCorePtrNew();
    VideoCapture video(argv[1]);
    INIReader ini(argv[2]);
    VideoWriter videoOut;

    if (ini.ParseError() != 0)
    {
        printf("Read failed\r\n");
        return 0;
    }

    bucket = ini.GetInteger("broiler", "bucket", -1);
    broiler_low = ini.GetInteger("broiler", "area_low", -1);
    broiler_hig = ini.GetInteger("broiler", "area_hig", -1);
    broiler_rate_low = ini.GetReal("broiler", "rate_low", -1);
    broiler_rate_hig = ini.GetReal("broiler", "rate_hig", -1);
    canny_thresh = ini.GetInteger("broiler", "canny", 100);

    video_w = video.get(CAP_PROP_FRAME_WIDTH);
    video_h = video.get(CAP_PROP_FRAME_HEIGHT);

    printf("File=%s\r\n", argv[1]);
    printf("\tParameter; Bucket=%d; Area_low=%d; Area_hig=%d; rate_low=%f; rate_hig=%f; canny=%d\r\n", 
                bucket,
                broiler_low,
                broiler_hig,
                broiler_rate_low,
                broiler_rate_hig,
                canny_thresh);
    if (!video.isOpened())
    {
        printf("Video could not opened\r\n");
        return -1;
    }


    Mat frame;
    Mat frameHSL;
    Mat frameBuck;
    Mat frameBuck1;
    Mat frameCanny;
    RNG rng(12345);
    vector<vector<Point>> vhulls;

    vhulls.push_back(vector<Point>());

    namedWindow(szWin, WINDOW_AUTOSIZE);
    namedWindow(szHSL, WINDOW_AUTOSIZE);

    int ex = static_cast<int>(video.get(CAP_PROP_FOURCC));
    videoOut.open("out_pinnacle.avi", 
                    ex, 
                    video.get(CAP_PROP_FPS),
                    Size(video_w, video_h),
                    true);

    vector<Rect> vRc;
    int frameIdx = 0;
    for (;;)
    {
        frameIdx++;
        video >> frame;

        if (frame.empty())
        {
            break;
        }

        ccp->bucketingColor(frame, bucket, frameBuck);
        cvtColor(frameBuck, frameHSL, COLOR_BGR2HLS);
        cvtColor(frameBuck, frameBuck1, COLOR_BGR2GRAY);

        Mat drawing = Mat::zeros( frame.size(), CV_8UC3 );

        if (frameIdx % 15 == 1)
        {
            Canny(frameBuck1,  frameCanny, canny_thresh, canny_thresh * 2);
            findContours(frameCanny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

            if (frameIdx < 10)
            {
                char szTmp[255];
                sprintf(szTmp, "bucket_%d.png", frameIdx);
                imwrite(szTmp, frameBuck);
            }

            vRc.clear();
            for (int i=0; i<contours.size(); ++i)
            {
                cv::Rect rc;    // bound rect
                ccp->contourRect(contours[i], rc);

                if (rc.width > 0)
                {
                    double ratio = (double)rc.height / (double)rc.width;
                    int area = rc.width * rc.width;

                    if (ratio >= broiler_rate_low && ratio <= broiler_rate_hig && area >= broiler_low && area <= broiler_hig)
                    {
                        rectangle(frame, rc, Scalar(255,255,0));
                        rectangle(frameBuck, rc, Scalar(255,255,0));

                        vRc.push_back(rc);
                    }
                }
            }

            for (int i=0; i<contours.size(); ++i)
            {
                Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
                drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
            }

            ccp->convexHull(contours, vhulls[0]);
            drawContours(drawing, vhulls, 0, Scalar(0,0,255), 1);
        }
        else
        {
            for (int i=0; i<vRc.size();++i)
            {
                rectangle(frame, vRc[i], Scalar(255,255,0));
                rectangle(frameBuck, vRc[i], Scalar(255,255,0));
            }

            for (int i=0; i<contours.size(); ++i)
            {
                Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
                drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
            }

            ccp->convexHull(contours, vhulls[0]);
            drawContours(drawing, vhulls, 0, Scalar(0,0,255), 1);
        }

        videoOut << frame;

        imshow(szHSL, frameHSL);
        imshow(szWin, frame);
        imshow(szBuckwet, frameBuck);
        imshow("contours", drawing);

        char c = (char)waitKey(25);
        if (c == 27) break;
    }
    
    return 0;
}