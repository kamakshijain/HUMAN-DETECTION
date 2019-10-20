/**
 * @author sayan brahma
 * @file train.cpp
 * @copyright [2019] kamakshi jain and Sayan Brahma
 * @brief Train class stub implementation
 */

#include<train.hpp>
/*
 * @brief This is the constructor for the class
 */
Train::Train() {
}

/*
 * @brief This function outputs the support vectors of the classifier.
 * @return A double vector containing the support vectors.
 */
std::vector<float> Train::getClassifier() {
    std::vector<float> hogDetector;
    return hogDetector;
}
/*
 * @brief This function extracts HOG descriptors from an image
 * @param It is the window size used for HOG feature extraction
 * @param Vector containing the images whose features need to be extracted
 */
void Train::getHOGfeatures(const cv::Size windowSize,
                           const std::vector<cv::Mat> & imgList) {
}
/**
 * @brief This function trains the SVM Classifier
 * @param saveClassifier Whether to save the trained classifier or not
 * @param classifierName Name of the classifer to be saved
 */
void Train::trainSVM(const bool saveClassifier = false,
                     const cv::String classifierName = "") {
}
/**
 * @brief Destructor of the train class
 */
Train::~Train() {
    std::cout << "Class Train has been Destroyed" << std::endl;
}

