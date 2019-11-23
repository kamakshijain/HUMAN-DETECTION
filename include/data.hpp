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
    /*
     * @brief  It gives the size of the image list.
     * @param This function takes the type of imgList - positive or negative 
     * @return This function returns the size of the imgList asked for.
     */
    int getImgListSize(const cv::String);

    /*
     * @brief It gives the image list as an output.
     * @param This function takes the type of imgList type - positive or negative 
     * @return This function returns the imgList asked for.
     */
    std::vector<cv::Mat> getImgList(const cv::String);
    /**
     * @brief Private variables declaration
     */
    /**
     * @brief Destructor for data class
     */
    ~Data();
 private:
    std::vector<cv::Mat> posImgList, negImgList;
};

#endif  // INCLUDE_DATA_HPP_
