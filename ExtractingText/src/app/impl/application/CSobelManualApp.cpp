#include "CSobelManualApp.h"
#include "app/impl/cv/CCVCore.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <memory>

using namespace std;
using namespace cv;

CSobelManualApp::CSobelManualApp()
{

}
CSobelManualApp::~CSobelManualApp()
{

}

int CSobelManualApp::run(int argc, char const *argv[])
{
    shared_ptr<ICVCore> p = make_shared<CCVCore>();

    if (argc < 2)
    {
        printf("Usage: %s <<image>>\r\n", argv[0]);
        return -1;
    }

    Mat dst;
    Mat img = imread(argv[1], IMREAD_ANYCOLOR);

    if (img.empty())
    {
        printf("Invalid image\r\n");
    }
    else
    {
        const char* szSource = "Source";
        const char* szSobel = "Sobel";

        p->sobel(img, dst);

        namedWindow(szSource, WINDOW_AUTOSIZE);
        namedWindow(szSobel, WINDOW_AUTOSIZE);
        
        imshow(szSource, img);
        imshow(szSobel, dst);

        waitKey();
    }
    return 0;
}