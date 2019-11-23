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
 * @file train.hpp
 * @copyright [2019] kamakshi jain, Sayan Brahma
 * @brief This is the stub for the Train class
 */

#ifndef INCLUDE_TRAIN_HPP_
#define INCLUDE_TRAIN_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "data.hpp"

/*
 * @brief Train is a class
 */
class Train {
 private:
  Data & allData;
  cv::Ptr<cv::ml::SVM> classifier;
  std::vector<cv::Mat> gradientList;

 public:
  std::vector<int> labels;

  /*
   * @brief This is the constructor for the class
   *
   * @param It takes a reference to class Data as input.
   *
   * @return It does not return any output. It initializes the classifier and
   *         if successful, prints a statement.
   */
  explicit Train(Data &);

  /*
   * @brief This is the first method of the class. It outputs the support
   *        vectors of the classifier.
   *
   * @param This method does not take any input.
   *
   * @result The output is a float vector containing the support vectors of
   *         the classifier.
   */
  std::vector<float> getClassifier();

  /*
   * @brief This is the second method of the class. It extracts HOG features
   *        from the given images.
   *
   * @param The first parameter is the window size to be used for HOG feature
   *        extraction.
   * @param The second parameter is a vector containing the images whose
   *        feature are to be extracted.
   *
   * @return This method does not give any output. It just populates the
   *         gradientList variable
   */
  void getHOGfeatures(const cv::Size, const std::string &);

  /*
   * @brief This is the third method of the class. It trains the SVM
   *        classifier.
   *
   * @param The first parameter is a boolean which commands the method to
   *        either save or not save the classifier.
   * @param The second parameter is the name of the classifier if it is to be
   *        saved.
   *
   * @return This method does not give any output. It trains the classifier
   *         and store it as a private variable.
   */
  void trainSVM(const bool, const cv::String);

  /*
   * @brief This is the fourth method of the class. It gives the size of the
   *        gradient list.
   *
   * @param This method does not take any input.
   *
   * @return This method outputs the size of the gradient list.
   */
  int getListSize();

  /*
   * @brief This is the fifth method of the class. It sets the classifier for
   *        the class.
   *
   * @param This method takes the classifier as input.
   *
   * @return This method does not give any output. It simply sets the value
   *         for the private variable "classifier".
   */
  void setClassifier(const cv::Ptr<cv::ml::SVM>);

  /*
   * @brief This is the sixth method of the class. It returns the classifier
   *        for the class.
   *
   * @param This method does not take any input.
   *
   * @return This method returns the classifier.
   */
  cv::Ptr<cv::ml::SVM> getDefaultClassifier();

  /*
   * @brief This is the seventh method of the class. It reads all the data.
   *
   * @param The first parameter defines the path to the directory where all
   *        annotations are defined.
   * @param The second parameter defines the path to the directory where all
   *        positive images are stored.
   * @param The third parameter defines the path to the directory where all
   *        negative images are stored.
   * @param The fourth parameter defines the size of the window to be used
   *        for resizing/cropping the images.
   * @param The fifth parameter commands the method to either show or not
   *        show the loaded positive images.
   *
   * @return This method returns a flag which states whether the data was
   *         read successfully or not.
   */
  bool readData(const cv::String, const cv::String, const cv::String,
                const cv::Size, const bool);

  /*
   * @brief This is the destructor for the class
   *
   * @param It does not take any input.
   *
   * @return It does not return any output. It just prints a statement.
   */
  ~Train();
};

#endif  // INCLUDE_TRAIN_HPP_

