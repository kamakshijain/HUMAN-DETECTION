/**
 * @author sayan brahma
 * @file detect.cpp
 * @copyright [2019] kamakshi jain and Sayan Brahma
 * @brief Detect class stub implementation
 */
#include<detect.hpp>

/**
 * @brief Constructor for Detect class
 */

Detect::Detect(): m(Default), hog(), hog_user() {
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    hog_user.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
/*
 * @brief This is the first method of the class. It toggles between the Default mode and User mode.
 */
void Detect::toggleMode() {
    // Ternary operator for changing the switch mode
    m = (m == Default ? User : Default);
}

/**
 * @brief This function gets the current working mode
 * @return A string with mode name
 */
std::string Detect::modeName() const {
    return (m == Default ? "Default" : "User");
}

/**
 * @brief This Function produces the bounding box around the humans
 * @param img input image
 * @return a vector containing coordinates of the box
 */
std::vector<cv::Rect> Detect::findHumans(const cv::InputArray img) {
    std::vector<cv::Rect> found;
    return found;
}
/**
 * @brief This function adjusts the bounding box around the human after being detected
 * @param r The bounding box already detected
 */
void Detect::adjustBoundingBox(cv::Rect & r) {
}

/*
 * @brief This function is used to test the trained classifier
 * @param testDir Passes the test directory address
 * @param size Window size where the testing should be done
 * @param Commands the method to either show or not show the images.
 * @param mode Working mode of the classifier - Default or the user preferred
 * @return The bounding box coordinates
 */
cv::Rect Detect::testClassifier(const cv::String testDir, const cv::Size size,
            const bool dispImage = true, const std::string &mode = "Default") {
    cv::Rect R;
    return R;
}

/**
 * @brief Destructor of the class
 */
Detect::~Detect() {
    std::cout << "Class Detect has been Destroyed" << std::endl;
}

