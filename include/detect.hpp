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
 * @file detect.hpp
 * @copyright [2019] kamakshi jain, Sayan Brahma
 * @brief This is the stub for the Detect class
 */

#ifndef INCLUDE_DETECT_HPP_
#define INCLUDE_DETECT_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class Detect {
/**
 * @brief Enum declaration with 2 options
 */
    enum Mode { Default, User } m;
    // since c++ 11 - enum name : type ;
    /**
     * @brief Public methods declaration
     *
     */
 public:
    cv::HOGDescriptor hog, hog_user;
	/**
	 * @brief Constructor of the class Detect
	 */
    Detect();

    /**
     * @brief This function toggles between the Default mode and User mode.
     */
    void toggleMode();

    /**
     * @brief This function returns the current working mode
     * @return The working mode in string type
     */
    std::string modeName() const;
    /**
     * @brief This function provides a bounding box around the humans detected
     * @param The image on which human is to be detected
     * @return A vector containing the coordinates bounding box
     */
    std::vector<cv::Rect> findHumans(const cv::InputArray);

    /**
     * @brief This functions adjusts the bounding box around the humans
     * @param The bounding box detected from the detectHumans finction
     */
    void adjustBoundingBox(cv::Rect &);

    /*
     * @brief This function is used to test the trained classifier
     * @param directory address of the test set
     * @param image size of the testing image
     * @param Commands the method to either show or not show the images.
     * @param mode of testing the classifier
     * @return Coordinates the bounding box based on the test results
     */
    cv::Rect testClassifier(const cv::String, const cv::Size,
                            const bool, const std::string &);

    /**
     * @brief Destructor of the Detect class
     */
    ~Detect();
};

#endif  // INCLUDE_DETECT_HPP_

