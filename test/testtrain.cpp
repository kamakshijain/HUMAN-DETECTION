/**
 *  @file testtrain.cpp
 *  Copyright [2019] kamakshi jain, Sayan Brahma
 *  @author Kamakshi Jain, Sayan Brahma
 *  @brief This is the test file to do test for train class
 */

#include <gtest/gtest.h>
#include <data.hpp>
#include <train.hpp>

// Unit test for getHOGfeatures method of class Train
TEST(TrainTest, TrainGetHOGTest) {
  Data testData;
  Train test;
  testData.loadNegImages("../data/test/neg", cv::Size(200, 200));
  test.getHOGfeatures(cv::Size(200, 200), testData.getNegImgList());
  // Check if the gradientList is being filled
  ASSERT_GT(test.getGradientList().size(), 0);
}

// Unit test for trainSVM method of class Train
TEST(TrainTest, TrainSVMTest) {
  Data testData;
  testData.loadPosImages("../data/test/annotations", "../data/test/pos",
                                          cv::Size(200, 200), false);
  testData.loadNegImages("../data/test/neg", cv::Size(200, 200));
  Train test;
  test.getHOGfeatures(cv::Size(200, 200), testData.getPosImgList());
  size_t posCount = test.getGradientList().size();
  test.labels.assign(posCount, 1);
  test.getHOGfeatures(cv::Size(200, 200), testData.getNegImgList());
  size_t negCount = test.getGradientList().size() - posCount;
  test.labels.insert(test.labels.end(), negCount, -1);
  // Check if the classifier is empty initially
  ASSERT_TRUE(test.classifier->getSupportVectors().empty());
  test.trainSVM(false, "");
  // Check if there is the classifier is non-empty after training
  ASSERT_TRUE(!test.classifier->getSupportVectors().empty());
}

// Unit test for getClassifier method of class Train
TEST(TrainTest, TrainGetClassifierTest) {
  Data testData;
  testData.loadPosImages("../data/test/annotations", "../data/test/pos",
                                          cv::Size(200, 200), false);
  testData.loadNegImages("../data/test/neg", cv::Size(200, 200));
  Train test;
  test.getHOGfeatures(cv::Size(200, 200), testData.getPosImgList());
  size_t posCount = test.getGradientList().size();
  test.labels.assign(posCount, 1);
  test.getHOGfeatures(cv::Size(200, 200), testData.getNegImgList());
  size_t negCount = test.getGradientList().size() - posCount;
  test.labels.insert(test.labels.end(), negCount, -1);
  test.trainSVM(false, "");
  // Check if the getClassifier gives a non-empty output
  ASSERT_NE(test.getClassifier().size(), 0);
}
