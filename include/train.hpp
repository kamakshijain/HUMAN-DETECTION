/**
 * @author kamakshi
 * @file train.hpp
 * @copyright [2019] kamakshi jain
 * @brief This is the stub for the train class
 */

#ifndef INCLUDE_TRAIN_HPP_
#define INCLUDE_TRAIN_HPP_

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class Train {
/**
 * @brief Public methods and constructors declaration
 */
 public:
	/**
	 * @brief Constructor for the class Train
	 */
    Train();
    /**
     * @brief This function is for extracting the HOG features from an image
     * @param The window size for HOG feature extractor
     * @param The image whose HOG features are to be extracted
     */
    void GetHogFeatures(const cv::Size, const std::vector<cv::Mat> &);
    /**
     * @brief This function trains the SVM classifier from the HOG features
     * @param If we want to save the classifier after training
     * @param name of the classifier ,if to be saved
     */
    void TrainSVM(const bool, const cv::String);
    /**
     * @brief This function gives the support vectors of the classifier
     * @return a double type vector
     */
    std::vector<double> GetClassifier();
    /**
     * @brief Destructor of the Train class
     */
    ~Train();

  cv::Ptr<cv::ml::SVM> getClassifier() const {
    return classifier;
  }

  void setClassifier(cv::Ptr<cv::ml::SVM> classifier) {
    this->classifier = classifier;
  }

  std::vector<cv::Mat> getGradList() const {
    return gradList;
  }

  void setGradList(std::vector<cv::Mat> gradList) {
    this->gradList = gradList;
  }

  std::vector<int> getLabels() const {
    return labels;
  }

  void setLabels(std::vector<int> labels) {
    this->labels = labels;
  }

/**
 * @brief Private variable declaration
 */
 private:
    cv::Ptr<cv::ml::SVM> classifier;
    std::vector<cv::Mat> gradList;
    std::vector<int> labels;
};
#endif  // INCLUDE_TRAIN_HPP_
