#include "CSVMApp.h"

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include <app/impl/background/CMatrix.h>
#include "app/interface/general/stdex.h"
#include <numeric>
#include <vector>

using namespace cv;
using namespace cv::ml;
using namespace std;

CSVMApp::CSVMApp()
{}

CSVMApp::~CSVMApp()
{}

int CSVMApp::run(int argc, char const *argv[])
{
    return vertically_extract("data/in", "data/out");
    // return extract_every_characters(argv[1]);

    // Set up training data
    int labels[4] = {1, -1, -1, -1};
    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
    Mat trainingDataMat(4, 2, CV_32F, trainingData);
    Mat labelsMat(4, 1, CV_32SC1, labels);
    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);
    // Data for visual representation
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);
    // Show the decision regions given by the SVM
    Vec3b green(0,255,0), blue(255,0,0);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            float response = svm->predict(sampleMat);
            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }
    }
    // Show the training data
    int thickness = -1;
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness );
    circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness );
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness );
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness );
    // Show support vectors
    thickness = 2;
    Mat sv = svm->getUncompressedSupportVectors();
    for (int i = 0; i < sv.rows; i++)
    {
        const float* v = sv.ptr<float>(i);
        circle(image,  Point( (int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thickness);
    }
    imwrite("result.png", image);        // save the image
    imshow("SVM Simple Example", image); // show it to the user
    waitKey();
    return 0;
}

int CSVMApp::run2()
{
    // Setup Training data
    int lables[4] = {1, -1, -1, -1};
    float trainingData[4][2] = {{501,10}, {255,10}, {501,255}, {10, 501}};
    Mat trainingDataMat(4, 2, CV_32F, trainingData);
    Mat lablesMat(4, 1, CV_32SC1, lables);

    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, lablesMat);

    // Data for visual representation
    int width = 512;
    int height = 512;
    
    Mat image = Mat::zeros( height, width, CV_8UC3 );
    Vec3b green(0,255,0), blue(255,0,0);
    
    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j, i);
            float response = svm->predict(sampleMat);

            if (response == 1)
                image.at<Vec3b>(i,j) = green;
            else if (response == -1)
                image.at<Vec3b>(i,j) = blue;
        }
    }

    // Show the training data
    int thickness = -1;
    circle( image, Point(501, 10), 5, Scalar(0,0,0), thickness);
    circle( image, Point(255, 10), 5, Scalar(255,255,255), thickness);
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness);
    circle( image, Point(10, 501), 5, Scalar(255,255,255), thickness);

    thickness = 2;
    Mat sv = svm->getUncompressedSupportVectors();

    
    for(int i = 0; i < sv.rows; i++)
    {
        /* code */
        const float* v = sv.ptr<float>(i);
        circle(image, Point((int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thickness);
    }
    imwrite("result.png", image);
    imshow("SVM Simple Example", image);
    waitKey();

    return 0;
}

int CSVMApp::run3()
{
    // Gradient descent
    // Generate random data
    int NUM = 3;
    int MAX_WIDTH = 500;
    int MAX_HEIGHT = 500;
    float training[NUM][2];
    int labels[NUM];

    for (int i=0;i<NUM;i++)
    {
        training[i][0] = rand() % MAX_WIDTH;
        training[i][1] = rand() % MAX_HEIGHT;

        labels[i] = rand() % 2;
    }

    Mat mat_TrainData(NUM, 2, CV_32F, training);
    Mat mat_Labels(NUM, 1, CV_32SC1, labels);
    
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(mat_TrainData, ROW_SAMPLE, mat_Labels);

    Mat image = Mat::zeros( MAX_HEIGHT, MAX_WIDTH, CV_8UC3 );
    Vec3b green(0,255,0), blue(255,0,0);

    for(int i = 0; i < image.rows; i++)
    {
        for(int j = 0; j < image.cols; j++)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j, i);
            float response = svm->predict(sampleMat);

            if (response == 1)
                image.at<Vec3b>(i,j) = green;
            else if (response == 0)
                image.at<Vec3b>(i,j) = blue;
        }
    }

    // Show the training data
    int thickness = -1;

    for (int i=0;i<NUM;i++)
    {
        if (labels[i] == 1)
        {
            circle( image, Point(training[i][0], training[i][1]), 5, Scalar(0,0,0), thickness);
        }
        else if (labels[i] == 0)
        {
            circle( image, Point(training[i][0], training[i][1]), 5, Scalar(255,255,255), thickness);
        }
    }

    thickness = 2;
    Mat sv = svm->getUncompressedSupportVectors();

    for(int i = 0; i < sv.rows; i++)
    {
        /* code */
        const float* v = sv.ptr<float>(i);
        circle(image, Point((int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thickness);
    }
    imwrite("result.png", image);
    imshow("SVM Simple Example", image);
    waitKey();

    return 0;
}

int CSVMApp::run4()
{
    Matrix<double> m1; // = new CMatrix();
    Matrix<double> m2; // = new CMatrix();
    Matrix<double> m3;
    CMatrix ctrl;

    m1.Rebuild(1,2);
    m2.Rebuild(2,1);

    m1.set(0,0,1);
    m1.set(0,1,1);
    m2.set(0,0,1);
    m2.set(1,0,1);

    ctrl.MatrixProduct(m1,m2,m3);

    cv::Mat img;

    // Extracdt
    

    printf("Result(rows,cols)=(%d,%d); [%f,%f]\r\n", m3.rows(), m3.cols(), m3.get(0,0), m3.get(0,1));
    return 0;
}

int CSVMApp::extract_every_characters(const char* szImgFile)
{

    cv::Mat img_src =  imread(szImgFile, IMREAD_GRAYSCALE);
    cv::Mat img;

    cv::threshold(img_src, img, 150, 255, CV_THRESH_BINARY_INV);
    cv::Mat rowSum;
    cv::Mat colSum;

    imshow("img_src", img_src);
    imshow("img", img);
    waitKey();

    cv::Mat mTest;

    mTest.create(2, 2, CV_64FC1);
    for (int y=0; y < mTest.rows; ++y)
    {
        for (int x=0; x<mTest.cols; ++x)
        {
            mTest.at<double>(y,x) = y * x * 1.1;
        }
    }

    printf("Matrix: \r\n");
    for (int y=0; y < mTest.rows; ++y)
    {
        for (int x=0; x<mTest.cols; ++x)
        {
            printf("%f; ", 
                (*(mTest.ptr<double>(0) + y * mTest.cols + x))
            );
        }
        printf("\r\n");
    }
    printf("\r\n");

    if (!img.empty())
    {
        rowSum.create(img.rows, 1, CV_64FC1);   // double; Mat::create are always continuous
        colSum.create(img.cols, 1, CV_64FC1);   // double; Mat::create are always continuous

        int size_in_bytes = img.rows * img.cols;
        
        if (img.isContinuous())
        {
            uchar* p = img.ptr<uchar>(0);
            for (int row=0;row<img.rows;++row)
            {
                // 
                // rowSum is continous 
                // rowSum.at(row,0) = value
                (*(rowSum.ptr<double>(0) + row)) = 
                    std::accumulate(
                        p + img.cols * row,
                        p + img.cols * (row + 1),
                        0.0);
            }

            for (int col=0;col<img.cols;++col)
            {
                // 
                // colSum is continous
                // 
                (*(colSum.ptr<double>(0) + col)) = 
                    stdex::accumulate(
                        p + col,
                        p + col + size_in_bytes,
                        0.0,
                        img.rows
                    );
            }
        }
        else
        {
            for (int row=0;row<img.rows;++row)
            {
                (*(rowSum.ptr<double>(0) + row)) = 
                    std::accumulate(
                        img.ptr<uchar>(row),
                        img.ptr<uchar>(row) + img.cols,
                        0.0
                    );
            }

            for (int col=0;col<img.cols;++col)
            {
                double sum = 0;
                for (int row=0;row < img.cols; ++row)
                {
                    sum += *(img.ptr<uchar>(row) + col);
                }

                (*(colSum.ptr<double>(0) + col)) = sum;
            }
        }

        // 
        // Print every details
        // 
        printf("Rowsum:\r\n");

        for (int row=0; row<img.rows;++row)
        {
            printf("%f; ", (*(rowSum.ptr<double>(0) + row)));
        }
        printf("\r\n");
        printf("Colsum:\r\n");
        for (int col=0;col<img.cols;++col)
        {
            printf("%f; ", (*(colSum.ptr<double>(0) + col)));
        }
        printf("\r\n");


        vector<Vec2i> vi;
        find_continuous_nonzero(rowSum, vi, 10);

        printf("Found %d ranges\r\n", vi.size());
        for (int i=0; i<vi.size(); ++i)
        {
            printf("(%d,%d); ", vi[i][0],vi[i][1]);
        }
        printf("\r\n");

        for (int i=0;i<vi.size();++i)
        {
            cv::Mat img_extract = cv::Mat(img_src, cv::Rect(0, vi[i][0], img_src.cols, vi[i][1] - vi[i][0]));
            char szBuff[255];
            sprintf(szBuff, "extract_%02d.png", i);

            imwrite(szBuff, img_extract);
        }
    }
    else 
    {
        printf("Empty image\r\n");
    }
    return 0;
}

int CSVMApp::homogeneous_geometry()
{
    // Homogeneouss

    // 
    // Eucliean => Homogeneuos
    // 
    cv::Mat P_Euclid;
    cv::Mat P_Homo;

    P_Euclid.create(2, 1, CV_64FC1);
    P_Homo.create(P_Euclid.rows + 1, 1, CV_64FC1);

    P_Euclid.at<double>(0,0) = 3.0;
    P_Euclid.at<double>(1,0) = 4.0;

    P_Homo.at<double>(0,0) = P_Euclid.at<double>(0,0);
    P_Homo.at<double>(1,0) = P_Euclid.at<double>(1,0);
    P_Homo.at<double>(2,0) = 1;

    // 
    // Homogeneous comparision (P_Homo01 == P_Homo02)
    // 
    cv::Mat P_Homo01;
    cv::Mat P_Homo02;
    double u;
    double v;
    double w;
    double scale = 2.2;

    P_Homo01.at<double>(0,0) = u;
    P_Homo01.at<double>(1,0) = v;
    P_Homo01.at<double>(2,0) = w;

    P_Homo02.at<double>(0,0) = u*scale;
    P_Homo02.at<double>(1,0) = v*scale;
    P_Homo02.at<double>(2,0) = w*scale;

    // 
    // Projective transformation
    // 
    return 0;
}

int CSVMApp::find_continuous_zero(
        const cv::Mat& sumVector,   // n x 1 matrix 
        std::vector<cv::Vec2i>& res, // Array of Vec2i(startlocation, endlocation) 
        int min_continous_len)
{
    if (sumVector.type() == CV_32SC1)
    {
        int s = -1; // Start location

        for (int i=0; i<=sumVector.rows; ++i)
        {
            if (i == sumVector.rows)
            {
                if (s >= 0 && i - s >= min_continous_len)
                {
                    // Yield result
                    res.push_back(Vec2i(s, i));
                }
            }
            else if (sumVector.at<int>(i,0) == 0)
            {
                if (s == -1)
                {
                    s = i;      // Start marking
                }
            }
            else  // (sumVector.at<double>(i,0) > 0)
            {
                if (s >= 0)
                {
                    if (i - s >= min_continous_len)
                    {
                        res.push_back(Vec2i(s, i));
                    }
                    s = -1;
                }
            }
        }
    }
    else if (sumVector.type() == CV_64FC1)
    {
        int s = -1; // Start location

        for (int i=0; i<=sumVector.rows; ++i)
        {
            if (i == sumVector.rows)
            {
                if (s >= 0 && i - s >= min_continous_len)
                {
                    // Yield result
                    res.push_back(Vec2i(s, i));
                }
            }
            else if (sumVector.at<double>(i,0) == 0)
            {
                if (s == -1)
                {
                    s = i;      // Start marking
                }
            }
            else  // (sumVector.at<double>(i,0) > 0)
            {
                if (s >= 0)
                {
                    if (i - s >= min_continous_len)
                    {
                        res.push_back(Vec2i(s, i));
                    }
                    s = -1;
                }
            }
        }
    }
    else 
    {
        throw "unsupported format. Please set vector to Int or double element.";
    }
    return 0;
}        

int CSVMApp::find_continuous_nonzero(
        const cv::Mat& sumVector,   // n x 1 matrix 
        std::vector<cv::Vec2i>& res, // Array of Vec2i(startlocation, endlocation) 
        int min_continous_len)
{
    if (sumVector.type() == CV_32SC1)
    {
        int s = -1; // Start location

        for (int i=0; i<=sumVector.rows; ++i)
        {
            if (i == sumVector.rows)
            {
                if (s >= 0 && i - s >= min_continous_len)
                {
                    // Yield result
                    res.push_back(Vec2i(s, i));
                }
            }
            else if (sumVector.at<int>(i,0) > 0)
            {
                if (s == -1)
                {
                    s = i;      // Start marking
                }
            }
            else  // (sumVector.at<double>(i,0) > 0)
            {
                if (s >= 0)
                {
                    if (i - s >= min_continous_len)
                    {
                        res.push_back(Vec2i(s, i));
                    }
                    s = -1;
                }
            }
        }
    }
    else if (sumVector.type() == CV_64FC1)
    {
        int s = -1; // Start location

        for (int i=0; i<=sumVector.rows; ++i)
        {
            if (i == sumVector.rows)
            {
                if (s >= 0 && i - s >= min_continous_len)
                {
                    // Yield result
                    res.push_back(Vec2i(s, i));
                }
            }
            else if (sumVector.at<double>(i,0) > 0)
            {
                if (s == -1)
                {
                    s = i;      // Start marking
                }
            }
            else  // (sumVector.at<double>(i,0) > 0)
            {
                if (s >= 0)
                {
                    if (i - s >= min_continous_len)
                    {
                        res.push_back(Vec2i(s, i));
                    }
                    s = -1;
                }
            }
        }
    }
    else 
    {
        throw "unsupported format. Please set vector to Int or double element.";
    }
    return 0;
}

int CSVMApp::vertically_extract(const char* szFolderIn, const char* szFolderOut)
{
    /*
     * @List of work
     *  W01. Get all images
     *  W02. For each image: process one.
     *  W03. For each image.
     *  
     */
    std::vector<std::string> v;

    boost::filesystem::path p1(szFolderIn);

    if (boost::filesystem::is_directory(p1))
    {
        for (boost::filesystem::directory_entry& x: boost::filesystem::directory_iterator(p1))
        {
            if (boost::filesystem::is_regular_file(x))
            {
                cout << x << endl;
                cout << "\t" <<  x.path().filename().root_path() << endl;

                // Here 
                // vertically_extract_a_file(x.path().c_str(), x.path().filename().c_str() ,szFolderOut);
            }
        }
    }


    return 0;
}

int CSVMApp::vertically_extract_a_file(const char* szFile, const char* prefix, const char* szFolderOut)
{
    printf("Process %s, %s\r\n", szFile, szFolderOut);
    cv::Mat img_src =  imread(szFile, IMREAD_GRAYSCALE);
    cv::Mat img;

    cv::threshold(img_src, img, 150, 255, CV_THRESH_BINARY_INV);
    cv::Mat rowSum;
    cv::Mat colSum;

    if (!img.empty())
    {
        rowSum.create(img.rows, 1, CV_64FC1);   // double; Mat::create are always continuous
        colSum.create(img.cols, 1, CV_64FC1);   // double; Mat::create are always continuous

        int size_in_bytes = img.rows * img.cols;
        
        if (img.isContinuous())
        {
            uchar* p = img.ptr<uchar>(0);
            for (int row=0;row<img.rows;++row)
            {
                // 
                // rowSum is continous 
                // rowSum.at(row,0) = value
                (*(rowSum.ptr<double>(0) + row)) = 
                    std::accumulate(
                        p + img.cols * row,
                        p + img.cols * (row + 1),
                        0.0);
            }

            for (int col=0;col<img.cols;++col)
            {
                // 
                // colSum is continous
                // 
                (*(colSum.ptr<double>(0) + col)) = 
                    stdex::accumulate(
                        p + col,
                        p + col + size_in_bytes,
                        0.0,
                        img.cols    // Jump step
                    );
            }
        }
        else
        {
            for (int row=0;row<img.rows;++row)
            {
                (*(rowSum.ptr<double>(0) + row)) = 
                    std::accumulate(
                        img.ptr<uchar>(row),
                        img.ptr<uchar>(row) + img.cols,
                        0.0
                    );
            }

            for (int col=0;col<img.cols;++col)
            {
                double sum = 0;
                for (int row=0;row < img.cols; ++row)
                {
                    sum += *(img.ptr<uchar>(row) + col);
                }

                (*(colSum.ptr<double>(0) + col)) = sum;
            }
        }

        vector<Vec2i> vi;
        find_continuous_nonzero(colSum, vi, 10);

        printf("Found %d ranges\r\n", vi.size());
        for (int i=0; i<vi.size(); ++i)
        {
            printf("(%d,%d); ", vi[i][0],vi[i][1]);
        }
        printf("\r\n");

        for (int i=0;i<vi.size();++i)
        {
            cv::Mat img_extract = cv::Mat(img_src, cv::Rect(vi[i][0], 0, vi[i][1] - vi[i][0], img_src.rows));
            char szBuff[255];
            sprintf(szBuff, "%s/%s_extract_vertical_%03d.png", szFolderOut, prefix, i);
            imwrite(szBuff, img_extract);
        }
    }
    else 
    {
        printf("Empty image\r\n");
    }
    return 0;
}