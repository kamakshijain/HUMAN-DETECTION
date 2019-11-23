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
#include <opencv2/opencv.hpp>
#include "data.hpp"

/*
 * @brief Train is a class
 */
class Train : public Data {
	/**
	 * @brief Public methods and constructors declaration
	 */
 public:
    
    std::vector<int> labels;
	/**
	 * @brief Constructor for the class Train
	 */
    Train();
    /**
     * @brief This function gives the support vectors of the classifier
     * @return a float type vector
     */
    std::vector<float> getClassifier();
    /**
     * @brief This function is for extracting the HOG features from an image
     * @param The window size for HOG feature extractor
     * @param The image whose HOG features are to be extracted
     */
    void getHOGfeatures(const cv::Size, const cv::String);
    /**
     * @brief This function trains the SVM classifier from the HOG features
     * @param If we want to save the classifier after training
     * @param name of the classifier ,if to be saved
     */
    void trainSVM(const bool, const cv::String);
    /*
     * @brief It gives the size of the gradient list.
     * @return This function outputs the size of the gradient list.
     */
    int getListSize();

    /*
     * @brief It sets the classifier for the class.
     * @param This function takes the classifier as input.
     */
    void setClassifier(const cv::Ptr<cv::ml::SVM>);

    /*
     * @brief It returns the classifier for the class.
     * @return This function returns the classifier.
     */
    cv::Ptr<cv::ml::SVM> getDefaultClassifier();
    /**
     * @brief Destructor of the Train class
     */
    ~Train();

    const std::vector<cv::Mat>& getGradientList() const {
    return gradientList;
    }

    void setGradientList(const std::vector<cv::Mat> &gradientLis) {
        gradientList = gradientLis;
    }

 private:
    std::vector<cv::Mat> gradientList;
    cv::Ptr<cv::ml::SVM> classifier;
};

#endif  // INCLUDE_TRAIN_HPP_
