#include "CCitizenIDApp.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face.hpp>
#include <opencv2/objdetect.hpp>
#include "app/impl/cv/CCVCore.h"
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::face;

CCitizenIDApp::CCitizenIDApp()
{}

CCitizenIDApp::~CCitizenIDApp()
{}

int CCitizenIDApp::run(int argc, char const* argv[])
{
    return liveness_check();
    // 1st 
    //   * Align the Image
    //   * Implement HoughLine first
    //   * Then Alignment The text (Anti Rotation)  
    // * Align the Image
    //   * Implement HoughLine first.
    //   * 
    // 

    // HoughLine
    // HoughLine & perform 
    //  * Perform HoughLinesP

    Mat src = imread( argv[1], IMREAD_COLOR);
    Mat dst;
    Mat cdst;
    Mat cdstP;

    if (src.empty())
    {
        printf("invalid\r\n");
        return -1;
    }
    
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();

    // Standard HoughLine transform
    vector<Vec2f> lines;
    
    // 
    // @Find@ related images with reverse image search 
    // 
    
    Mat gray;
    Mat thresh;

    cv::cvtColor(src, gray, COLOR_BGR2GRAY);
    cv::bitwise_not(gray, gray);  // Black => white & white to black 
    cv::threshold(gray, thresh, 0.0, 255.0, THRESH_BINARY | THRESH_OTSU);   // Foreground to 255, background to 0

    imshow("thresh", thresh);

    vector<Point> points;
    for (int y=0; y<thresh.rows;++y)
    {
        for (int x=0; x<thresh.cols; ++x)
        {
            if (thresh.at<uchar>(y,x) > 0)
            {
                //points.push_back(cv::Point2i(x, y));
                points.push_back(cv::Point2i(y, x));
            }
        }
    }

    cv::RotatedRect rr = cv::minAreaRect(points);

    float angle;
    if (rr.angle < -45)
    {
        angle = -(90 - rr.angle);
    }
    else
    {
        angle = -rr.angle;
    }
    printf("Angles=%f; %f\r\n", rr.angle, angle);

    // cv::Mat M = cv::getRotationMatrix2D(cv::Point2f( thresh.cols/2, thresh.rows/2), angle, 1.0);
    cv::Mat M = cv::getRotationMatrix2D(cv::Point2f( thresh.rows/2, thresh.cols/2), angle, 1.0);
    cv::warpAffine(src, dst, M, cv::Size(src.cols, src.rows), INTER_CUBIC, BORDER_REPLICATE);

    ICVCorePtr ccptr = CCVCorePtrNew();
    cv::Mat gauss;
    ccptr->calc_Gaussian2DKernel(5, gauss);

    cout << "Gauss " << gauss << endl;

    Mat grayorigin;
    Mat lowfreq;
    Mat imgblur;
    Mat sqi;
    Mat sqi_norm;

    cvtColor(src, grayorigin, CV_BGR2GRAY);

    calc_low_frequency_image(grayorigin, lowfreq, 5);

    // cv::GaussianBlur(grayorigin, imgblur, cv::Size(3, 3), 0.0);
    cv::divide(gray, lowfreq, sqi);
    // cv::divide(grayorigin, imgblur, sqi);
    cv::normalize(sqi, sqi_norm, 0.0, 255.0, cv::NORM_MINMAX);
    
    printf("OK\r\n");
    imshow("input", src);
    imshow("rotated", dst);
    // imshow("blur", imgblur);
    imshow("lowfreq", lowfreq);
    imshow("SQI", sqi_norm);
    waitKey();

    // Face recognition
    return 0;
}

int CCitizenIDApp::calc_low_frequency_image(cv::Mat inp, cv::Mat& out, int ksize)
{
    Mat mgauss;
    //ICVCorePtr cvcp = CCVCorePtrNew();
    CCVCore cvc;
    cvc.calc_Gaussian2DKernel(ksize, mgauss);

    if (inp.channels() != 1)
    {
        printf("Invalid\r\n");
        return -1;
    }

    out.create(inp.size(), inp.type());
    Mat F; //  = cv::Mat::zeros(cv::Size(ksize, ksize), CV_64FC1);
    Mat W; //  = cv::Mat::zeros(cv::Size(ksize, ksize), CV_64FC1);
    uchar depth = inp.type() & CV_MAT_DEPTH_MASK;

    F.create(cv::Size(ksize, ksize), CV_64FC1);
    W.create(cv::Size(ksize, ksize), CV_64FC1);
    
    printf("HERE\r\n");
    for (int y=0; y<inp.rows;++y)
    {
        for (int x=0; x<inp.cols;++x)
        {
            printf("HERE(%d,%d)\r\n", y,x);
            double Ti = mean_a_subrange(inp, y, x, ksize);

            printf("Ti=%f\r\n", Ti);
            
            for (int ky=0; ky<W.rows;++ky)
            {
                for (int kx=0; kx<W.cols;++kx)
                {
                    W.at<double>(ky,kx) = inp.at<uchar>(y,x) < Ti ? 0 : 1;
                    F.at<double>(ky,kx) = W.at<double>(ky,kx) * mgauss.at<double>(ky,kx);
                }
            }

            if (depth == CV_8U || depth == CV_8S)
            {
                printf("TypeUChar");
                out.at<uchar>(y, x) = (uchar)convolve_element(inp, F, y, x);
            }
            else if (depth == CV_32S || depth == CV_32F)
            {
                printf("TypeInt");
                out.at<int>(y, x) = (uchar)convolve_element(inp, F, y, x);
            }
            else if (depth == CV_64F)
            {
                printf("TypeDouble");
                out.at<double>(y, x) = (uchar)convolve_element(inp, F, y, x);
            }
            else 
            {
                printf("No Datatype");
            }
        }
    }
    return 0;
}

double CCitizenIDApp::mean_a_subrange(cv::Mat inp, int y, int x, int ksize)
{
    double ret = 0.0;

    int x0;
    int y0;

    x0 = x - ksize/2;
    y0 = y - ksize/2;

    if (x0 <= 0) x0 = 0;
    if (y0 <= 0) y0 = 0;

    int w = min(ksize, inp.cols - x0);
    int h = min(ksize, inp.rows - y0);

    cv::Mat roi = cv::Mat(inp, cv::Rect(x0, y0, w, h));
    cv::Scalar mean = cv::mean(roi);
    return mean.val[0];
}

double CCitizenIDApp::convolve_element(cv::Mat inp, cv::Mat kernel, int y, int x, int kcenterx, int kcentery)
{
    double ret = 0.0;
    int cx;
    int cy;

    if (kcenterx == -1)
    {
        kcenterx = kernel.cols/2;
    }

    if (kcentery == -1)
    {
        kcentery = kernel.rows/2;
    }

    for (int irow=0; irow<kernel.rows;++irow)
    {
        for (int icol=0; icol<kernel.cols; ++icol)
        {
            int inpx = x + (icol - kcenterx);
            int inpy = y + (irow - kcentery);

            if (inpx >=0 && inpx < inp.cols && inpy >=0 && inpy < inp.rows)
            {
                ret += inp.at<uchar>(inpy, inpx) * kernel.at<double>(irow,icol);
            }
        }
    }

    return ret;
}

int CCitizenIDApp::hamming_distance(cv::Mat img1, cv::Mat img2)
{
    assert(img1.size() == img2.size());
    int score = 0;
    
    for (int y=0; y<img1.rows;++y)
    {
        for (int x=0; x<img1.cols;++x)
        {
            score += img1.at<uchar>(y,x) == img2.at<uchar>(y,x) ? 1 : 0;
        }
    }

    return score;
}

bool CCitizenIDApp::MyDetector(InputArray image, OutputArray faces, CascadeClassifier *face_cascade)
{
    Mat gray;

    if (image.channels() > 1)
        cvtColor(image, gray, COLOR_BGR2GRAY);
    else
        gray = image.getMat().clone();

    equalizeHist(gray, gray);

    std::vector<Rect> faces_;
    face_cascade->detectMultiScale(gray, faces_, 1.4, 2, CASCADE_SCALE_IMAGE, Size(30, 30));
    Mat(faces_).copyTo(faces);

    return true;
}

int CCitizenIDApp::liveness_check()
{
    /* 
     * 
     * Illumination invariant 
     * 
     * 
     */
    cv::CascadeClassifier face_cascade;
    cv::Mat img;
    std::string filename;
    std::string cascade_name;
    FacemarkKazemi::Params params;

    face_cascade.load("lbpcascade_frontalface.xml");
    Ptr<FacemarkKazemi> facemark = FacemarkKazemi::create(params);

    facemark->setFaceDetector((FN_FaceDetector)CCitizenIDApp::MyDetector, &face_cascade);
    facemark->loadModel("trained_model_may_26th.dat");

    cv::VideoCapture video(0);  // Webcam 
    std::vector<cv::Rect> faces;
    std::vector<std::vector<Point2f>> shapes;
    
    if (!video.isOpened())
    {
        printf("Invalid\r\n");
        return -1;
    }

    Mat frame;
    for (;;)
    {
        video >> frame;

        if (frame.empty())
        {
            break;
        }

        faces.clear();
        shapes.clear();

        // Face detection
        facemark->getFaces(frame, faces);
        
        // Rotate 
        if (faces.size() == 0)
        {
            // No face
        }
        else 
        {
            for( size_t i = 0; i < faces.size(); i++ )
            {
                cv::rectangle(img,faces[i],Scalar( 255, 0, 0 ));
            }
            //vector to store the landmarks of all the faces in the image
            // if(facemark->fit(img,faces,shapes))
            // {
            //     for(unsigned long i=0;i<faces.size();i++){
            //         for(unsigned long k=0;k<shapes[i].size();k++)
            //             cv::circle(img,shapes[i][k],3,cv::Scalar(0,0,255),FILLED);
            //     }
            // }

            // (shapes[i][k])
            // Rotate images 

            // 
        }

        imshow("video", frame);

        if (waitKey(25) == 27)
        {
            break;
        }

        
    }



    video.release();
    return 0;
}

