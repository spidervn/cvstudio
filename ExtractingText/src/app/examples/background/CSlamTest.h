#ifndef EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CSLAMTEST_H_
#define EXTRACTTEXT_APP_EXAMPLES_BACKGROUND_CSLAMTEST_H_

#include "app/interface/IApplication.h"
#include <atomic>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <mutex>
#include <opencv2/core.hpp>

// 
// Data structure for SLAM 
// 

#define MATRIX_EQUAL(m1,m2) (cv::sum(m1 != m2) == cv::Scalar(0,0,0,0))
#define MYASSERT(b,strTrue,strFalse) { if (b) { std::cout << strTrue << std::endl;} else { std::cout << strFalse << std::end; } }

struct keyframe;
struct map_database {};

struct landmark
{
    // General information
    unsigned int id;
    static std::atomic<unsigned int> next_id_;  // Next ID 


    unsigned int first_keyfrm_id_ = 0;
    unsigned int num_observations_ = 0;

    // Variables for frame tracking
    cv::Vec2d reproj_in_tracking_;
    float x_right_in_tracking_;

    bool is_observable_in_tracking_;
    int scale_level_in_tracking_;

    unsigned int identifier_in_local_map_update_ = 0;
    unsigned int identifier_in_local_lm_search_ = 0;

    // Variables for loop-closing
    unsigned int loop_fusion_identifier_ = 0;
    unsigned int ref_keyfr_id_in_loop_fusion_ = 0;
    cv::Vec3d pos_w_after_global_BA;
    unsigned int loop_BA_identifier_ = 0;


    // Privates
    cv::Vec3d pos_w_;
    std::map<keyframe*, unsigned int> observations_;
    cv::Vec3d mean_normal_;
    cv::Mat descriptor_;
    
    keyframe* ref_keyfrm_;  // Reference keyframe

    // Track counter 
    unsigned int num_observable_ = 1;
    unsigned int num_observed_ = 1;

    bool will_be_erased_ = false;   // Will be erased shortly or not 
    landmark* replaced;

    // ORB scale variances 
    // max valid distance between landmark and camera 
    float min_valid_dist_ = 0;
    float max_valid_dist_ = 0;

    // Map database 
    map_database* map_db_;

    mutable std::mutex mtx_position_;
    mutable std::mutex mtx_observations_;
};

struct keypoint
{

};

struct KeyFrameSLAM
{
    double camera_image;
    double inverse_depth_map;
    double variance_inverse_depth;

    // Depth map & variance are only defined 
    
};

struct MapSLAM
{

};

//==================================
class CSlamTest: public IApplication
{
private:
    /* data */
public:
    CSlamTest(/* args */);
    ~CSlamTest();

    int run(int argc, char const *argv[]);

    
protected:
    int test_transformation();
    int random_matrix(cv::Mat& m, cv::RNG& rng);

    int rigid3d_transformation();
    int translation_pos(cv::Mat m, cv::Mat m_trans);

    int rotate2D();

    int gaussian_filters_test();
};

#endif