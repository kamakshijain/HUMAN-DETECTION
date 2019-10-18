/*
 * @file maincpp
 *
 * @author: sayan Brahma
 * @copyright [2019] Sayan Brahma
 * @brief main function implementation
 */

#include <data.hpp>
#include <train.hpp>
#include <detect.hpp>

int main() {
    std::cout << "This is a Human Detector program" << std::endl;
    std::cout << "This used a HOG descriptor and "
             "SVM classifier for human detection" << std::endl;
    std::cout << std::endl;
    // Defining window size
    cv::Size windowSize = cv::Size(96, 160);
    // Training or Testing of a classifier
    std::cout << "Do you want to Train the Classifier? (y/n): " << std::endl;
    std::string trainDetector;
    // Getting the entered line/address
    getline(std::cin, trainDetector);
    // Adding all the arrays and converting them to lower case
    std::transform(trainDetector.begin(), trainDetector.end(),
                       trainDetector.begin(), ::tolower);
    // If the entered choic is yes then ...
    if (trainDetector == "yes" || trainDetector == "y"
            || trainDetector == "Y") {
             // Positive Images path
            std::cout << "Give the Positive Training Images address else press"
            " enter to use the default one";
            std::string posDir;
            getline(std::cin, posDir);
            if (posDir.empty())
                posDir = "../data/INRIAPerson/Train/pos/";


            // Annotations path
            std::cout << "Give the Annotations file path for Positive " <<
            "training Images else press enter to use the default";
            std::string annotationPath;
            getline(std::cin, annotationPath);
            if (annotationPath.empty())
            annotationPath = "../data/INRIAPerson/"
            "Train/annotations/";

            // Negative images path
            std::cout << "Give the Positive Training Images address else press"
            " enter to use the default one";
            std::string negDir;
            getline(std::cin, negDir);
            if (negDir.empty())
            negDir = "../data/INRIAPerson/Train/neg/";

            // load Positive images
            Data allData;
            std::cout << "Loading Positive Images" << std::endl;
            allData.LoadPosImages(static_cast<cv::String>(annotationPath),
            static_cast<cv::String>(posDir), windowSize);
            // Check if images were successfully loaded
            if (allData.posImageList.size() > 0) {
            std::cout << "Loading Positive Training Data Complete" << std::endl;
            } else {
            std::cout << "No images found. " <<
            "Please check the Path Directory: " << posDir << std::endl;
            return 0;
             }

            // load negative images
            std::cout << "Loading Negative Images" << std::endl;
            allData.LoadNegImages(static_cast<cv::String>(negDir), windowSize);
            if (allData.negImageList.size() > 0) {
            std::cout << "Loading Negative Training Data Complete" << std::endl;
            } else {
            std::cout << "No images found. " <<
            "Please check the Path Directory: " << negDir << std::endl;
            return 0;
            }
    }
}

