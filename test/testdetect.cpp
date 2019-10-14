/*
 * @file testdetect.cpp
 * @copyright [2019] kamakshi jain
 * Created on: Oct 13, 2019
 * @author: kamakshi
 * @brief This is the test file which contains the test conditions for detect class
 */

#include <gtest/gtest.h>
#include <detect.hpp>

/**
 * @brief This is a test condition to check the if in working mode(default parameters)
 *        or user mode (parameters are set by user)
 */
TEST(detectTest, modeNameTest) {
    Detect test;
  // Check if the mode is initialized to Default
  ASSERT_EQ("Default", test.GetMode());
}
