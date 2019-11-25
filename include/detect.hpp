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
 * @author kamakshi jain, Sayan Brahma
 * @file detect.hpp
 * @copyright [2019] kamakshi jain, Sayan Brahma
 * @brief This is the stub for the Detect class
 */

#ifndef INCLUDE_DETECT_HPP_
#define INCLUDE_DETECT_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

/*
 * @brief Detector is a class
 */
class Detect {
 private:
  enum Mode {
    Default,
    User
  } m;

 public:
  cv::HOGDescriptor hog, hog_user;

  /*
   * @brief This is the constructor for the class
   *
   * @param It does not take any input.
   *
   * @return It does not return any output. It just initializes the HOG
   *         descriptors and then prints a statement.
   */
  Detect();

  /*
   * @brief This is the first method of the class. It toggles between the
   *        Default mode and User mode.
   *
   * @param It does not take any input.
   *
   * @return It does not return any output. It just toggles the current mode.
   */
  void toggleMode();

  /*
   * @brief This is the second method of the class. It returns the name of
   *        the current mode.
   *
   * @param It does not take any input.
   *
   * @return This method returns the mode name as a string.
   */
  std::string modeName() const;

  /*
   * @brief This is the third method of the class. It returns the bounding
   *        boxes around the humans found in the image.
   *
   * @param This method takes an image as input.
   *
   * @return This method returns a vector containing the object Rect which
   *         defines the bounding box around the detected humans.
   */
  std::vector<cv::Rect> findHumans(const cv::InputArray);

  /*
   * @brief This is the fourth method of the class. It adjusts the bounding
   *        box created around a detected human.
   *
   * @param This method takes the bounding box detected as input.
   *
   * @param It does not give any output. It adjusts the bounding boxes and
   *        the updated values are stored in the input itself which is given
   *        as a reference.
   */
  void adjustBoundingBox(cv::Rect &);

  /*
   * @brief This is the fifth method of the class. It is used to test the
   *        trained classifier.
   *
   * @param The first parameter defines the testDir where the testing set is
   *        stored.
   * @param The second parameter is the window size or the image size at
   *        which testing is done.
   * @param The third parameter commands the method to either show or not
   *        show the images.
   * @param The fourth parameter defines the mode to be used for testing the
   *        classifier.
   *
   * @result This method returns the rectangle when testing.
   */
  cv::Rect testClassifier(const cv::String, const cv::Size, const bool,
                          const std::string &);

  /*
   * @brief This is the destructor for the class
   *
   * @param It does not take any input.
   *
   * @return It does not return any output. It just prints a statement.
   */
  ~Detect();
};

#endif  // INCLUDE_DETECT_HPP_

