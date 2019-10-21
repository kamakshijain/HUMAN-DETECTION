/**
 * @author kamakshi jain, Sayan Brahma
 * @file data.hpp
 * @copyright [2019] kamakshi jain , Sayan Brahma
 * @brief This is the stub for the Data class
 */

#ifndef INCLUDE_DATA_HPP_
#define INCLUDE_DATA_HPP_

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

/*
 * @brief Data is a class
 */
class Data {
	/**
	 * @brief Public methods declaration
	 */
 public:
    /*
     * @brief This is the constructor for the class
     */
    Data();

    /**
     * @brief Loads the positive training image set
     * @param The path to the directory to the annotations
     * @param The path to the positive images dataset
     * @param Resizing window for the image
     */
    void loadPosImages(const cv::String, const cv::String,
                       const cv::Size, const bool);

    /**
     * @brief Loads the negative training set images
     * @param The path to the directory to -ve images
     * @param Resizing window for the image
     */
    void loadNegImages(const cv::String, const cv::Size);

    /**
     * @brief Destructor for data class
     */
    ~Data();

    const std::vector<cv::Mat>& getNegImgList() const {
    return negImgList;
    }

    void setNegImgList(const std::vector<cv::Mat> &negImgLis) {
    negImgList = negImgLis;
    }

    const std::vector<cv::Mat>& getPosImgList() const {
    return posImgList;
    }

    void setPosImgList(const std::vector<cv::Mat> &posImgLis) {
    posImgList = posImgLis;
    }
    /**
     * @brief Private variables declaration
     */
 private:
    std::vector<cv::Mat> posImgList, negImgList;
};

#endif  // INCLUDE_DATA_HPP_
