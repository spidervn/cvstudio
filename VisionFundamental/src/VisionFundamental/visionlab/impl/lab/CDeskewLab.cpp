#include "CDeskewLab.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace cv;
using namespace std;

CDeskewLab::CDeskewLab(/* args */)
{
}

CDeskewLab::~CDeskewLab()
{
}

int CDeskewLab::run(int argc, char const* argv[])
{
    return 0;
}

int CDeskewLab::skewangle_est(const char* file)
{
    cv::Mat img;
    cv::Mat bw;
    cv::Scalar mean;

    std::string strImgfile;
    int w;
    int h;

    int re_min, re_max, ce_min, ce_max;     // Extended bounding box 
    int c_min, c_max, r_min, r_max;         // Bounding box

    vector<double> vDt; // Distance array from top of bounding box
    vector<double> vDb; // Distance array from bottom of bounding box
    vector<double> vDtf;    // Erosion of distance array
    vector<double> vDbf;    // Erosion of distance array
    vector<double> vdDtf;   // derivatives of Erosion of distance array
    vector<double> vdDbf;   // derivatives of Erosion of distance array

    double z = 2.0;
    double k1 = 10.0;
    double k2 = 50.0;
    int h = 4;
    bool bInputValid = true;

    // Input 

    std::ifstream fi;
    fi.open(file);
    if (!fi)
    {
        print("Invalid file\r\n");
        return -1;
    }

    bInputValid = bInputValid && (fi >> c_min);
    bInputValid = bInputValid && (fi >> r_min);
    bInputValid = bInputValid && (fi >> w);
    bInputValid = bInputValid && (fi >> h);

    if (!bInputValid)
    {
        printf("Invalid input\r\n");
        return -1;
    }

    c_max = c_min + w;
    r_max = r_min + h;
    
    // 
    // Deskew for Card Image Scanning
    // 
    std::filesystem::path pathInput(file);
    std::filesystem::path pathImg  =  pathInput.parent_path() + strImgfile;


    // Start Algorithm
    img = imread(pathImg.c_str(), IMREAD_GRAYSCALE);
    mean = cv::mean(img);
    int imean =  (int)mean[0];

    cv::threshold(img, bw, imean, 255, CV_THRESH_BINARY);
    ce_min = std::max(0, c_min - (c_max-c_min)/4);
    ce_max = std::min(img.cols - 1, c_max + (c_max - c_min)/4);
    re_min = std::max(0, r_min - (r_max - r_min)/4);
    re_max = std::min(img.rows - 1, r_max + (r_max - r_min)/4);

    int reH = re_max - re_min;
    for (int c=ce_min;c<=ce_max;++c)
    {
        vDt.push_back(0.0);
        vDb.push_back(0.0);

        vDtf.push_back(0.0);
        vDbf.push_back(0.0);

        vdDbf.push_back(0.0);
        vdDtf.push_back(0.0);
    }

    for (int c=ce_min;c<=ce_max;++c)
    {    
        // vDt
        int r_min;

        for (int r=re_min;r<=re_max;++r)
        {
            // Black
            if (bw.at<uchar>(r,c) == 0)
            {
                r_min = r;
                break;
            }
        }

        if (r_min > reH)
        {
            r_min = reH;
        }

        vDt[c] = r_min;

        // vDb
        r_min = reH;
        for (int r=re_max;r>=re_min;--r)
        {
            if (bw.at<uchar>(r, ce_max - c) == 0)
            {
                r_min = r;
                break;
            }
        }

        if (r_min > reH)
        {
            r_min = reH;
        }
        vDb[c] = r_min;
    }

    // Erosion
    {
        for (int i=0; i<vDb.size();++i)
        {
            vDtf[i] = vDt[i];
            vDbf[i] = vDb[i];


            for (int j=i-h;j<i+h;++j)
            {
                if (j>=0 && j<vDb.size())
                {
                    if (vDtf[i] > vDt[i])
                    {
                        vDtf[i] = vDt[i];
                    }

                    if (vDbf[i] > vDb[i])
                    {
                        vDbf[i] = vDb[i];
                    }
                }
            }
        }
    }

    // Derivatives
    {
        for (int i=h; i<vDtf.size()-h-1;++i)
        {
            vdDtf.push_back(vDtf[i+h] - vDtf[i-h]);
            vdDbf.push_back(vDbf[i+h] - vDbf[i-h]);
        }
    }

    // Straight Lines
    {
        
    }
    return 0;
}

