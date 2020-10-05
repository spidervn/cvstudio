#include "CFaceApp.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facemark.hpp>
#include <opencv2/face/facemark_train.hpp>
#include <opencv2/face/facemarkAAM.hpp>
#include <opencv2/face/facemarkLBF.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace cv::face;
using namespace std;

//=========================================================
Conf::Conf(cv::String s, double d)
{
    model_path = s;
    scaleFactor = d;
    face_detector.load(model_path);
}

//=========================================================
CFaceApp::CFaceApp()
{}

CFaceApp::~CFaceApp()
{}

int CFaceApp::run(int argc, char const* argv[])
{
    return ex04(argv[1]);
    return ex02(argv[1]);
    
    // calcSQI(argv[1]);
    return 0;
}

int CFaceApp::ex01(const char* file)
{
    Mat img;
    Mat frame;

    img = imread(file, IMREAD_COLOR);
    frame = Mat::zeros(img.size(), img.type());
    Ptr<Facemark> facemark = createFacemarkLBF();
    std::vector<Rect> faces;
    std::vector<std::vector<Point2f> > landmarks;

    // facemark->getFaces(img, faces);
    facemark->fit(img, faces, landmarks);
    // 
    // for(int j=0;j<faces.size();j++){
    //     face::drawFacemarks(frame, landmarks[j], Scalar(0,0,255));
    // }

    // imshow("img", img);
    // imshow("frame", frame);
    // waitKey();
    return 0;
}

int CFaceApp::ex02(const char* file)
{
    Mat img;
    Mat frame;

    frame = imread(file, IMREAD_COLOR);
    std::vector<cv::Rect> faces;
    CParams params("haarcascade_frontalface_alt.xml");
    cv::face::getFaces(frame, faces, &params);
    for(int j=0;j<faces.size();j++){
        cv::rectangle(frame, faces[j], cv::Scalar(255,0,255));
    }
    cv::imshow("detection", frame);

    waitKey();
    return 0;
}

int CFaceApp::ex03(const char* file)
{
    FacemarkAAM::Params params;
    Ptr<FacemarkAAM> facemark;

    params.scales.push_back(2.0);
    params.scales.push_back(4.0);
    params.model_filename = "AAM.yaml";
    facemark = FacemarkAAM::create(params);
    
    return 0;
}

int CFaceApp::ex04(const char* file)
{
    FacemarkLBF::Params params;
    params.model_filename = "helen.model";
    Ptr<FacemarkLBF> facemark = FacemarkLBF::create(params);
    
    Conf config("lbpcascade_frontalface.xml", 1.4);
    facemark->setFaceDetector(CFaceApp::myDetector, (void*) &config);
    
    Mat img = imread(file);
    std::vector<cv::Rect> faces;
    facemark->getFaces(img, faces) ; // , config);

    for(int j=0;j<faces.size();j++){
        cv::rectangle(img, faces[j], cv::Scalar(255,0,255));
    }

    imshow("result", img);
    waitKey(0);
    return 0;
}

bool CFaceApp::myDetector(cv::InputArray img, cv::OutputArray faces, void* pconf)
{
    Conf* conf = (Conf*)pconf;
    Mat gray;
    if (img.channels() > 1)
        cvtColor(img, gray, COLOR_BGR2GRAY);
    else
        gray = img.getMat().clone();
    equalizeHist(gray, gray);
    std::vector<Rect> faces_;
    conf->face_detector.detectMultiScale(gray, faces_, conf->scaleFactor, 2, CASCADE_SCALE_IMAGE, Size(30, 30) );
    Mat(faces_).copyTo(faces);
    return true;
}

int CFaceApp::eigen_face(const char* file)
{
    // Image-analyzing.
    Mat m = imread(file, IMREAD_COLOR);
    int M;  // Dimensions on training image
    int N;  // Dimensional of vector image. N = row*col

    int h = m.rows;
    int w = m.cols;


    int numTrain;
    vector<Mat> vF;     // Trainning face data
    Mat avgF;           // Average face
    Mat mat_Cov;            // Co-variance matrix

    bool bValidSize = true;
    numTrain = vF.size();
    N = h*w;

    for (int i=1; i<vF.size();++i)
    {
        //if (vF[i].size() != vF[0].size())
        if (vF[i].size() != cv::Size(N,1))
        {
            bValidSize = false;
        }
    }

    assert(bValidSize);

    M = vF[0].rows * vF[0].cols;
    avgF = Mat::zeros(h, w, CV_64FC1);

    //
    // numTrain
    //
    for (int i=1; i<vF.size();++i)
    {
        for (int y=0; y<vF[i].rows;++y)
        {
            for (int x = 0; x < vF[i].cols; ++x)
            {
                avgF.at<double>(y,x) += vF[i].at<double>(y,x);
            }
        }
    }

    avgF = avgF / M;    // Average map
    // Covariance Matrix 
    //cov.create(N, N, CV_64FC1);
    //mat_Cov = Mat::zeros(N,N, CV_64FC1);

    // Covariance Matrix
    for (int i=0; i<N; ++i)
    {

        Mat mTmp = vF[i] - avgF;
        Mat mTmp_T;

        cv::transpose(mTmp, mTmp_T);
        mat_Cov += (mTmp * mTmp_T);

    }

    //
    // Covariance Matrix
    // 

    // 
    // Eigen vector calculation
    //  

    // 
    // Calculating Principal Component Analysis
    // 


    return 0;
}

int CFaceApp::eigen_vector(const cv::Mat& m, cv::Mat& vec_eigen, double& eigen_value)
{
    /*
     * M*vec_eigen = eigen_value * vec_eigen
     *  
     * Given M, find eigen_value and vec_eigen.
     *
     */

    cv::Mat v;  // Vector
    return 0;
}

void CFaceApp::calcSQI(const char* szFile)
{
    cv::Mat mat = imread(szFile, IMREAD_COLOR);
    cv::Mat gray;
    cv::Mat dst;

    cvtColor(mat, gray, COLOR_BGR2GRAY);

    //cv::GaussianBlur(gray, dst, cv::Size(5, 5), 0, 0);
    cv::blur(gray, dst, cv::Size(7, 7));
    cv::Mat sqi = gray/dst;
    cv::Mat sqi_norm;
    normalize(sqi, sqi_norm, 0, 255, NORM_MINMAX);
    

    imshow("src", mat);
    imshow("sqi", sqi_norm);

    waitKey();
}

void CFaceApp::lambertianModel()
{

}