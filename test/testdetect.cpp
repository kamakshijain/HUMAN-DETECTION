/*
 * @file testdetect.cpp
 * @copyright [2019] kamakshi jain, Sayan Brahma
 * Created on: Oct 13, 2019
 * @author: kamakshi, Sayan Brahma
 * @brief This is the test file which contains the test conditions for detect class
 */


#include <gtest/gtest.h>
#include <detect.hpp>

// Unit test for toggleMode method of class Detect
TEST(DetectTest, DetectToggleTest) {
  Detect test;
  test.toggleMode();
  // Check if the mode changed to User
  ASSERT_EQ("User", test.modeName());
}

// Unit test for modeName method of class Detect
TEST(DetectTest, DetectModeNameTest) {
  Detect test;
  // Check if the mode is initialized to Default
  ASSERT_EQ("Default", test.modeName());
}

// Unit test for findHumans method of class Detect
TEST(DetectTest, DetectHumansTest) {
  Detect test;
  cv::Rect orgBox(124, 26, 221, 442);  // [221 x 442 from (124, 26)]
  std::string imageName("../data/test/imgs/pedestrian_5.jpg");
  cv::Mat img = cv::imread(imageName);
  std::vector<cv::Rect> found = test.findHumans(img);
  cv::Rect &r1 = found.front();
  // Check if the detected box is close to the ground truth in Default Mode
  ASSERT_LT(orgBox.area() - (orgBox & r1).area(), 500);
  test.toggleMode();
  found = test.findHumans(img);
  cv::Rect &r2 = found.front();
  // Check if the detected box is close to the ground truth in User Mode
  ASSERT_LT(orgBox.area() - (orgBox & r2).area(), 500);
  // Check if the detected boxes using either methods are close to each other
  ASSERT_LT(r1.area() - (r1 & r2).area(), 500);
}

// Unit test for adjustBoundingBox method of class Detect
TEST(DetectTest, DetectAdjustBoxTest) {
  Detect test;
  std::string imageName("../data/test/imgs/pedestrian_5.jpg");
  cv::Mat img = cv::imread(imageName);
  std::vector<cv::Rect> found = test.findHumans(img);
  cv::Rect &r = found.front();
  cv::Rect orgBox = r;
  test.adjustBoundingBox(r);
  // Check if the bounding box has reduced after adjustment
  ASSERT_TRUE((0.63 <= static_cast<double>(r.area())/
    static_cast<double>(orgBox.area())) || (static_cast<double>(r.area())/
                              static_cast<double>(orgBox.area()) <= 0.65));
}

// Unit test for testClassifier method of class Detect
TEST(DetectTest, DetectTestClassifierTest) {
  Detect test;
  std::string imageName("../data/test/imgs/pedestrian_5.jpg");
  cv::Mat img = cv::imread(imageName);
  cv::resize(img, img, cv::Size(200, 200));
  std::vector<cv::Rect> found = test.findHumans(img);
  cv::Rect &orgBox = found.front();
  cv::Rect r = test.testClassifier("../data/test/imgs", cv::Size(200, 200),
                                                            false, "User");
  // Check if the bounding box computed by the two methods are close
  ASSERT_LT(orgBox.area() - (orgBox & r).area(), 500);
}

