/**
 * MIT License
 * 
 * Copyright (c) 2019 Sayan Brahma, Kamakshi Jain
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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
