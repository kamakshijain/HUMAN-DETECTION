/**
 *  @file testdata.cpp
 *  Copyright [2019] Kamakshi Jain
 *  @author Kamakshi Jain
 *  @brief This is the declaration of 1 unit test to be conducted, more tests might be added later on
 */

#include <gtest/gtest.h>
#include <data.hpp>

// Test loadPosImages function of the data class
TEST(dataTest, DataLoadPosImagesTest) {
  Data test;
  test.LoadPosImages("../data/test/annotations", "../data/test/pos",
                                          cv::Size(200, 200));
  // Check if the images are read
  EXPECT_GT(test.posImageList.size(), 0);  // Greater than 0 is expected
  bool imgSize = true;
  for (auto img : test.posImageList)
    if (img.size() != cv::Size(200, 200)) {
      imgSize = false;
      break;
    }
  // Check whether the read images are of 200 x 200
  EXPECT_TRUE(imgSize);
}
