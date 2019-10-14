/**
 * @author kamakshi jain
 * @file data.hpp
 * @copyright [2019] kamakshi jain
 * @brief This is the stub for the data class
 */

#ifndef INCLUDE_DATA_HPP_
#define INCLUDE_DATA_HPP_

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class Data {
/**
 * @brief Public methods declaration
 */
 public:
	/**
	 * @brief Contructor for data class
	 */
    Data();
    /**
     * @brief Loads the positive training image set
     * @param The path to the directory to the annotations
     * @param The path to the positive images dataset
     * @param Resizing window for the image
     */
    void LoadPosImages(const cv::String, const cv::String,
                           const cv::Size);
    /**
     * @brief Loads the negative training set images
     * @param The path to the directory to -ve images
     * @param Resizing window for the image
     */
    void LoadNegImages(const cv::String, const cv::Size);
    /**
     * @brief Destructor for data class
     */
    ~Data();

  std::vector<cv::Mat> getNegImageList() const {
    return negImageList;
  }

  void setNegImageList(std::vector<cv::Mat> negImageList) {
    this->negImageList = negImageList;
  }

  std::vector<cv::Mat> getPosImageList() const {
    return posImageList;
  }

  void setPosImageList(std::vector<cv::Mat> posImageList) {
    this->posImageList = posImageList;
  }

/**
 * @brief Private variables declaration
 */
 private:
    std::vector<cv::Mat> posImageList, negImageList;
};



#endif  // INCLUDE_DATA_HPP_
