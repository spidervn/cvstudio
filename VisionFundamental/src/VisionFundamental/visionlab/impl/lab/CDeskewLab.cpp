#include "CDeskewLab.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <cmath>

using namespace cv;
using namespace std;

#define RADIAN_25_DEGREE 0.436332313
#define RADIAN_38_DEGREE 0.663225116

CDeskewLab::CDeskewLab(/* args */)
{
}

CDeskewLab::~CDeskewLab()
{
}

int CDeskewLab::run(int argc, char const* argv[])
{
    skewangle_est(argv[1]);
    return 0;
}

double CDeskewLab::_bp(double x)
{
    if (x > RADIAN_38_DEGREE)
    {
        return 1.0;
    }
    return 0.0;
}

double CDeskewLab::_bn(double x)
{
    if (x < -RADIAN_38_DEGREE)
    {
        return 1;
    }
    return 0;
}

int CDeskewLab::skewangle_est(const char* file)
{
    cv::Mat img;
    cv::Mat bw;
    cv::Scalar mean;

    std::string strImgfile;
    int width;
    int height;

    int re_min, re_max, ce_min, ce_max;     // Extended bounding box 
    int c_min, c_max, r_min, r_max;         // Bounding box
    double phi;                             // Result
    double delta;

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
        printf("Invalid file\r\n");
        return -1;
    }

    bInputValid = bInputValid && (fi >> strImgfile);
    bInputValid = bInputValid && (fi >> c_min);
    bInputValid = bInputValid && (fi >> r_min);
    bInputValid = bInputValid && (fi >> width);
    bInputValid = bInputValid && (fi >> height);

    printf("File=%s\r\n", strImgfile.c_str());
    if (!bInputValid)
    {
        printf("Invalid input\r\n");
        return -1;
    }

    c_max = c_min + width;
    r_max = r_min + height;
    
    // 
    // Deskew for Card Image Scanning
    // 
    
    std::experimental::filesystem::path pathInput(file);
    std::experimental::filesystem::path pathImg  =  pathInput.parent_path(); // + strImgfile;

    pathImg = pathImg + "/" + strImgfile;
    printf("File=%s\r\n", pathImg.c_str());

    // Start Algorithm
    img = imread(pathImg.c_str(), IMREAD_GRAYSCALE);
    mean = cv::mean(img);
    int imean =  (int)mean[0];
    

    cv::threshold(img, bw, 2*imean/3, 255, CV_THRESH_BINARY);
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

    // Derivatives
    for (int i=h; i<vDtf.size()-h-1;++i)
    {
        vdDtf.push_back(vDtf[i+h] - vDtf[i-h]);
        vdDbf.push_back(vDbf[i+h] - vDbf[i-h]);
    }

    // Straight Lines
    int c = 0;
    int st1 = -1;
    int st2 = -1;
    vector<double> vStB; // Begin
    vector<double> vStE; // End
    vector<double> vSbB; // Begin
    vector<double> vSbE; // End

    // Find 
    while (c <= vdDtf.size());        
    {
        bool bYield = false;
        // End of array 
        if (c == vdDtf.size())
        {
            if (st1 >= 0)
            {
                st2 = c-1;
                bYield = true;
            }
        }
        else if (vdDtf[c] <= k1)
        {
            if (st1 < 0)
            {
                st1 = c;
            }
        }
        else // vdDtf[c] > k1
        {
            if (st1 >= 0)
            {
                st2 = c-1;  // The previous position where vdDtf[c-1] <= k1
                bYield = true;
            }
        }

        // If yield => we have range [st1,st2] which every i within[st1,st2], vdDtf[i] <= k1
        if (bYield)
        {
            // Check more condition
            if (st2 - st1 >= k2 && vDtf[st2] < 3*(re_max - re_min)/4)
            {
                // Accept 
                vStB.push_back(st1);
                vStE.push_back(st2);
            }

            // Clean flag
            st1 = -1;
            st2 = -1;
        }
        c++;
    }

    c = 0;
    int sb2 = -1;
    int sb1 = -1;
    while (c <= vdDbf.size())
    {
        bool bYield = false;
        // End of array
        if (c == vdDbf.size())
        {
            if (sb1 >= 0 && sb2 <0)
            {
                sb2 = vdDbf.size() - 1;
                bYield = true;
            }
            else if (vdDbf[c] <= k1)
            {
                if (sb1 < 0)
                {
                    sb1 = c;
                }
            }
            else // vdDbf[c] > k1
            {
                if (sb1 >= 0)
                {
                    sb2 = c-1;  // The previous position where vdDbf[c-1] <= k1
                    bYield = true;
                }
            }
        }

        // Yield [sb1,sb2]
        if (bYield)
        {
            if (sb2 - sb1 >= k2 && vdDbf[sb2] < 3*(re_max - re_min)/4)
            {
                vSbB.push_back(sb1);
                vSbE.push_back(sb2);
            }
        }
        c++;
    }

    int nB = vSbB.size();
    int nT = vStB.size();
    int N = nB + nT;
    vector<double> vDx;
    vector<double> vDy;
    vector<double> vAlpha;

    for (int i=0;i<N;++i)
    {
        vDx.push_back(0);
        vDy.push_back(0);
    }

    for (int i=0; i<nT; ++i)
    {
        vDx[i] = (vStE[i] - vStB[i] - 2*k1);
    }
    for (int j=0; j<nB; ++j)
    {
        vDx[j+nT] = (vSbE[j] - vSbB[j] - 2*k1);
    }

    for (int i=0; i<nT; ++i)
    {
        double dsum1 = 0.0;
        double dsum2 = 0.0;
        for (int k=-z; k<=z;++k)
        {
            dsum1 += vDtf[vStE[i] - k1 + k];
            dsum2 += vDtf[vStB[i] + k1 + k];
        }

        vDy[i] = (dsum1 - dsum2)/(2*z+1);
    }

    for (int j=0;j<nB;++j)
    {
        double dsum1 = 0.0;
        double dsum2 = 0.0;
        for (int k=-z; k<=z;++k)
        {
            if (vSbE[j] - k1 + k >=0 && vSbE[j] - k1 + k < vDbf.size())
            {
                dsum1 += vDbf[vSbE[j] - k1 + k];
            }
                
            if (vDtf[vStB[j] + k1 + k] >= 0 && vDtf[vStB[j] + k1 + k] < vDtf.size())
            {
                dsum2 += vDtf[vStB[j] + k1 + k];
            }
        }

        vDy[j + nT] = (dsum1 - dsum2)/(2*z+1);            
    }

    for (int i=0; i<N;++i)        
    {
        vAlpha.push_back( atan( (double)vDy[i]/(double)vDx[i]));
    }

    // 
    // Enter Iterations
    // Iterations are continued while variance delta > 1. 
    // 
    int loopid = 0;
    do
    {
        phi = 0;
        double dsum = 0;
        for (int i=0; i<N;++i)
        {
            phi += vAlpha[i] * vDx[i];
            dsum += vDx[i];
        }

        phi = phi / dsum;
        dsum = 0;
        for (int i=0; i<N; ++i)
        {
            dsum += (phi - vAlpha[i])*(phi - vAlpha[i]);
        }

        if (N != 1)
        {
            delta = sqrt(dsum)/(N-1);
        }
        else
        {
            throw "Exception";
        }

        double qap = 0.0;
        double qan = 0.0;
        double sap = 0.0;
        double san = 0.0;
        if (delta > RADIAN_25_DEGREE)
        {
            for (int i=0; i<N; ++i)
            {
                qap += _bp(vAlpha[i]);
                qan += _bn(vAlpha[i]);

                sap += vAlpha[i] * _bp(vAlpha[i]);
                san += vAlpha[i] * _bn(vAlpha[i]);
            }

            if (qap > 0 && qan > 0)
            {
                delta = 0;
            }

            if (sap > san)
            {
                phi = sap / qap;
            }
            else 
            {
                phi = san / qan;
            }
        }
        
        vector<double>::iterator it;
        vector<double>::iterator itdx;

        printf("Loop[%d]. Before Elimination\r\n", vAlpha.size());
        for (it = vAlpha.begin(), itdx = vDx.begin(); it != vAlpha.end() && itdx != vDx.end();)
        {
            if (*it < phi - delta || *it > phi + delta)
            {
                it = vAlpha.erase(it);
                itdx = vDx.erase(itdx);
                
            }
            else 
            {
                it++;
                itdx++;
            }
        }
        printf("\tAfter elimination\r\n", vAlpha.size());
        int ch = getchar();
    }
    while (delta > 1 && vAlpha.size() > 0);

    return 0;
}

