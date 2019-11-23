/*
 * MIT License
 *
 * Copyright (c) 2019 Sayan Brahma
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/*
 * @file MockData.hpp
 *
 *  Created on: 23-Nov-2019
 *      Author: sayan Brahma
 */

#ifndef INCLUDE_MOCKDATA_HPP_
#define INCLUDE_MOCKDATA_HPP_

#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "data.hpp"

/*
 * @brief MockData is a class
 */
class MockData : public Data {
 public:
  // Create mock methods for all the methods of class Data.
  MOCK_METHOD4(loadPosImages, void(const cv::String anotPath,
          const cv::String posDir, const cv::Size size,
const bool dispImg));
  MOCK_METHOD2(loadNegImages, void(const cv::String negDir,
const cv::Size size));
  MOCK_METHOD1(getImgListSize, int(const std::string & str));
};

#endif  // INCLUDE_MOCKDATA_HPP_

