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

/*
 * @brief Train is a class
 */
class Train {
	/**
	 * @brief Public methods and constructors declaration
	 */
 public:
    cv::Ptr<cv::ml::SVM> classifier;
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
    void getHOGfeatures(const cv::Size, const std::vector<cv::Mat> &);
    /**
     * @brief This function trains the SVM classifier from the HOG features
     * @param If we want to save the classifier after training
     * @param name of the classifier ,if to be saved
     */
    void trainSVM(const bool, const cv::String);
    /**
     * @brief Destructor of the Train class
     */
    ~Train();

    const std::vector<cv::Mat>& getGradientList() const {
    return gradientList;
    }

    void setGradientList(const std::vector<cv::Mat> &gradientList) {
        this->gradientList = gradientList;
    }

 private:
    std::vector<cv::Mat> gradientList;
};

#endif  // INCLUDE_TRAIN_HPP_
