/**
 * @author sayan brahma
 * @file data.cpp
 * @copyright [2019] kamakshi jain and Sayan Brahma
 * @brief Data class stub implementation
 */
#include<data.hpp>

/*
 * @brief This is the constructor for the class
 */
Data::Data() {
    std::cout << "Class Data has been Initialized" << std::endl;
}

/**
 * @brief This function draws a rectangle around a human in the pictures of positive image directory also can be used as ground truth
 * @param anotPath Path of the annotation file for positive images
 * @param posDir Path of the positive image directory
 * @param size the resize window of the image
 */
void Data::loadPosImages(const cv::String anotPath, const cv::String  posDir,
                         const cv::Size size, const bool dispImg = false) {
}

/**
 * @brief This function loads the negative images from the training dataset
 * @param dirName The name of the directory
 * @param size The size of the window of the images for sample
 */
void Data::loadNegImages(const cv::String dirName, const cv::Size size) {
}

/*
 * @brief This is the destructor for the class
 */
Data::~Data() {
    std::cout << "Class Data has been Destroyed" << std::endl;
}
