/**
 * @author kamakshi jain, Sayan brahma
 * @file testdata.cpp
 * @copyright [2019] kamakshi jain, Sayan brahma
 * @brief This is the test for the data class
 */

#include <gtest/gtest.h>
#include <data.hpp>

// Unit test loadPosImages method of class Data
TEST(DataTest, DataLoadPosImagesTest) {
  Data test;
  test.loadPosImages("../data/test/annotations", "../data/test/pos",
                                          cv::Size(200, 200), false);
  // Check if the images were read
  ASSERT_GT(test.getPosImgList().size(), 0);
  bool sizeMatch = true;
  for (auto img : test.getPosImgList())
    if (img.size() != cv::Size(200, 200)) {
      sizeMatch = false;
      break;
    }
  // Check if the images read have a size of 200 x 200
  ASSERT_TRUE(sizeMatch);
}

// Unit test for loadNegImages method of class Data
TEST(DataTest, DataLoadNegImagesTest) {
  Data test;
  test.loadNegImages("../data/test/neg", cv::Size(200, 200));
  // Check if the images were read
  ASSERT_GT(test.getNegImgList().size(), 0);
  bool sizeMatch = true;
  for (auto img : test.getNegImgList())
    if (img.size() != cv::Size(200, 200)) {
      sizeMatch = false;
      break;
    }
  // Check if the images read have a size of 200 x 200
  ASSERT_TRUE(sizeMatch);
}
