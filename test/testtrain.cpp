/**
 *  @file testtrain.cpp
 *  Copyright [2019] kamakshi jain
 *  @author Kamakshi Jain
 *  @brief This is the test file to do test for train class
 */
#include <gtest/gtest.h>
#include <data.hpp>
#include <train.hpp>
 /**
  * @brief This is a test condition to check the getHogFeaturesTest function
  */
TEST(trainTest1, getHogFeaturesTest) {
    Data testData;
    Train testTrain;
    testData.LoadNegImages("../data/test/neg", cv::Size(200, 200));
    testTrain.GetHogFeatures(cv::Size(200, 200), testData.negImageList);
    // Check if the gradList is non-empty
    ASSERT_GT(testTrain.gradList.size(), 0);
    // The expected value is greater than 0
    }
