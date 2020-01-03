#include "CLoadfontApp.h"
#include <opencv2/core/cvstd.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/freetype.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

CLoadfontApp::CLoadfontApp(/* args */)
{}

CLoadfontApp::~CLoadfontApp()
{

}

int CLoadfontApp::run(int argc, char const* argv[])
{
    String text = "Text inside box";
    int fontHeight = 20; //60;
    int thickness = -1;
    int linestype = 8;

    Mat img(600, 800, CV_8UC3, Scalar::all(0));

    int baseline = 0;
    cv::Ptr<cv::freetype::FreeType2> ft2;
    
    ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData("./Pacifico.ttf", 0);

    Size textSize = ft2->getTextSize(text, fontHeight, thickness, &baseline);

    if (thickness > 0)
    {
        baseline += thickness;
    }

    // center of the text
    Point textOrg((img.cols - textSize.width) / 2,
                    (img.rows + textSize.height) / 2);

    // draw the box
    // rectangle(img, textOrg + Point(0, baseline), 
    //             textOrg + Point(textSize.width, -textSize.height),
    //             Scalar(0, 255, 0), 1, 8);

    // ... & the baseline first
    // line(img, textOrg + Point(0, thickness), 
    //             textOrg + Point(textSize.width, thickness),
    //             Scalar(0, 0, 255), 1, 8 );

    ft2->putText(img, text, textOrg, fontHeight, Scalar::all(255), thickness, linestype, true);

    imshow("a", img);
    waitKey();

    return 0;
}