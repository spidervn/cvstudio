#include "CManualFundamentalApp.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <vector>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/connected_components.hpp"

using namespace cv;
using namespace boost;
using namespace std;

CManualFundamentalApp::CManualFundamentalApp(/* args */)
{
}

CManualFundamentalApp::~CManualFundamentalApp()
{
}

int CManualFundamentalApp::run(int argc, char const *argv[])
{
    Mat c = (Mat_<double>(3,1) << 1, 2, 3);
    Mat c1 = (Mat_<double>(1,3) << 2, 4, 6);
    Mat c3 = c*c1;

    c3.at<double>(2,1) = 0;
    std::cout << c << std::endl;
    std::cout << c1 << std::endl;
    std::cout << c3 << std::endl;


    Graph c(10);

    boost::add_vertex(c);
    boost::add_edge(0, 1, c);

    std::vector<int> component (boost::num_vertices (c));
    size_t num_components = boost::connected_components (c, &component[0]);

    std::cout << "Vertices in the first component:" << std::endl;
    for (size_t i = 0; i < boost::num_vertices(c); ++i)
    {
        if (component[i] == 0)
        {
            std::cout << i << " ";
        }
    }

    return 0;
}