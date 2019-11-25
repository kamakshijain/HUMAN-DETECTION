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
 *  @file testtrain.cpp
 *  Copyright [2019] kamakshi jain, Sayan Brahma
 *  @author Kamakshi Jain, Sayan Brahma
 *  @brief This is the test file to do test for train class
 */

#include <gtest/gtest.h>
#include "train.hpp"
#include "MockData.hpp"

// Unit test for first method of class Train
TEST(TrainTest, getClassifierTest) {
  Data allData;
  Train test(allData);
  test.readData("../data/test/annotations", "../data/test/pos",
      "../data/test/neg", cv::Size(200, 200), false);
  test.getHOGfeatures(cv::Size(200, 200), "positive");
  size_t posCount = test.getListSize();
  test.labels.assign(posCount, 1);
  test.getHOGfeatures(cv::Size(200, 200), "negative");
  size_t negCount = test.getListSize() - posCount;
  test.labels.insert(test.labels.end(), negCount, -1);
  test.trainSVM(false, "");
  // Check if the getClassifier gives a non-empty output
  ASSERT_NE(0, test.getClassifier().size());
}

// Unit test for second method of class Train
TEST(TrainTest, getHOGfeaturesTest) {
  Data allData;
  Train test(allData);
  test.readData("", "", "../data/test/neg", cv::Size(200, 200), false);
  test.getHOGfeatures(cv::Size(200, 200), "negative");
  // Check if the gradientList is being filled
  ASSERT_GT(test.getListSize(), 0);
}

// Unit test for third method of class Train
TEST(TrainTest, trainSVMTest) {
  Data allData;
  Train test(allData);
  test.readData("../data/test/annotations", "../data/test/pos",
      "../data/test/neg", cv::Size(200, 200), false);
  test.getHOGfeatures(cv::Size(200, 200), "positive");
  size_t posCount = test.getListSize();
  test.labels.assign(posCount, 1);
  test.getHOGfeatures(cv::Size(200, 200), "negative");
  size_t negCount = test.getListSize() - posCount;
  test.labels.insert(test.labels.end(), negCount, -1);
  // Check if the classifier is empty initially
  ASSERT_TRUE(test.getDefaultClassifier()->getSupportVectors().empty());
  test.trainSVM(false, "");
  // Check if the classifier is non-empty after training
  ASSERT_TRUE(!test.getDefaultClassifier()->getSupportVectors().empty());
  test.trainSVM(true, "../data/test/classifier/svmClassifier");
  // Check if the classifier is loaded correctly
  Data allData2;
  Train test2(allData2);
  test2.setClassifier(cv::ml::SVM::load
      ("../data/test/classifier/svmClassifier"));
  ASSERT_TRUE(!test2.getDefaultClassifier()->getSupportVectors().empty());
}

// Unit test for fourth method of class Train
TEST(TrainTest, getListSizeTest) {
  Data allData;
  Train test(allData);
  test.readData("", "", "../data/test/neg", cv::Size(200, 200), false);
  test.getHOGfeatures(cv::Size(200, 200), "negative");
  // Check if HOG features were extracted
  ASSERT_EQ(allData.getImgListSize("negative")*2, test.getListSize());
}

// Unit test for fifth method of class Train
TEST(TrainTest, setClassifierTest) {
  Data allData;
  Train test(allData);
  cv::Ptr<cv::ml::SVM> classifier = test.getDefaultClassifier();
  test.setClassifier(classifier);
  // Check if the classifiers are same
  ASSERT_TRUE(classifier == test.getDefaultClassifier());
}

// Unit test for sixth method of class Train
TEST(TrainTest, getDefaultClassifierTest) {
  Data allData;
  Train test(allData);
  // Check if the classifier retrieved is empty
  ASSERT_TRUE(test.getDefaultClassifier()->getSupportVectors().empty());
}

// Unit test for the seventh method of class Train
TEST(TrainTest, readDataTest) {
  Data allData;
  Train test(allData);
  // Call the method of class Train
  ASSERT_TRUE(test.readData("../data/test/annotations", "../data/test/pos",
          "../data/test/neg", cv::Size(200, 200), false));
}

// Mock test for class Train
TEST(TrainTest, mockTest) {
  MockData allData;
  Train test(allData);
  // Define mock tests
  cv::String anotPath = "../data/test/annotations",
  posDir = "../data/test/pos", negDir = "../data/test/neg";
  cv::Size size = cv::Size(200, 200);
  std::string pos = "positive", neg = "negative";
  ::testing::Expectation seq1 = EXPECT_CALL(allData, loadPosImages(anotPath,
          posDir, size, false)).Times(1);
  ::testing::Expectation seq2 = EXPECT_CALL(allData, getImgListSize(pos))
  .Times(1).After(seq1)
  .WillOnce(::testing::Return(0));
  ::testing::Expectation seq3 = EXPECT_CALL(allData, loadNegImages(negDir,
          size)).Times(1).After(seq1, seq2);
  EXPECT_CALL(allData, getImgListSize(neg))
  .Times(1).After(seq1, seq2, seq3).WillOnce(::testing::Return(0));
  // Call the method of class Train
  test.readData(anotPath, posDir, negDir, cv::Size(200, 200), false);
}

