/*
 * @file detect.cpp
 *
 * Created on: Oct 17, 2019
 * @author: sayan Brahma
 * @copyright [2019] Sayan Brahma
 * @brief Detect class implementation
 */

#include <detect.hpp>
/**
 * @brief Constructor for Detect class
 */
Detect::Detect(): m(Default), hogDefault(), hogUser() {
    hogDefault.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
    hogUser.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
}
/**
 *
 */
void Detect::switchMode() {
    // Ternary operator for changing the switch mode
    m = (m == Default ? User : Default);
}
/**
 * @brief This function gets the current working mode
 * @return A string with mode name
 */
std::string Detect::getMode() const {
    return (m == Default ? "Default" : "User");
}
/**
 * @brief This Function produces the bounding box around the humans
 * @param img input image
 * @return a vector containing coordinates of the box
 */
std::vector<cv::Rect> Detect::detectHumans(const cv::InputArray img) {
    std::vector<cv::Rect> found;
    if (m == Default) {
        std::cout << "Using in-Built Classifier" << std::endl;
        hogDefault.detectMultiScale(img, found);
    } else if (m == User) {
        std::cout << "Using User Trained Classifier" << std::endl;
        hogUser.detectMultiScale(img, found);
    }
    return found;
}
/**
 * @brief This function adjusts the bounding box around the human after being detected
 * @param r The bounding box already detected
 */
void Detect::adjustBoundingBox(cv::Rect & r) {
    r.x += cvRound(r.width*0.1);
    r.width = cvRound(r.width*0.8);
    r.y += cvRound(r.height*0.07);
    r.height = cvRound(r.height*0.8);
}
