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
/*
 * @file maincpp
 *
 * @author: sayan Brahma
 * @copyright [2019] Sayan Brahma
 * @brief main function implementation
 */

#include "detect.hpp"

/*
 * @brief This is a function to compare the strings (case-insensitive).
 * @param The first parameter is the first string.
 * @param The second parameter is the second string.
 * @return It returns true if the strings match and false otherwise.
 */
bool isEqual(std::string str1, std::string str2) {
    return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
                      [](char str1, char str2) {
                          return tolower(str1) == tolower(str2);
                      });
}

/*
 * @brief This is the main function of the project
 * @return It returns a 0 after successful implementation
 */
int main() {
    // Project starts
    std::cout << "This is a Human Detection Project." << std::endl;
    std::cout << "It uses a SVM classifier-trained using " <<
                 "HOG features to detect Humans." << std:: endl;
    std::cout << std::endl;

    // Define a window size
    cv::Size windowSize = cv::Size(96, 160);
    // Instantiate an object for class Detect
    Detect detector;
    // Training or Testing of a classifier
    std::cout << "Do you want to Train a Classifier? " << std::endl;
    std::cout << "y option will give you a training data demo and you "
           "well be getting a trained classifier stored in a file "
           "as an output" << std::endl;
    std::cout << "n option will give you a testing data demo and you "
           "well be getting pictures with humans"
           " detected and coordinates" << std::endl;
    std::string trainDetector;
    // Getting the entered line/address
    getline(std::cin, trainDetector);
    // Adding all the arrays and converting them to lower case
    std::transform(trainDetector.begin(), trainDetector.end(),
                   trainDetector.begin(), ::tolower);
    // If the entered choic is yes then ...
     if (isEqual(trainDetector, "yes") || isEqual(trainDetector, "y")) {
        // Positive Images path
        std::cout << "Give the Path for Positive Training "
         "Images else press enter " <<
        "(Default is set as '../data/INRIAPerson/Train/pos/'): ";
        std::string posDir;
        getline(std::cin, posDir);
        if (posDir.empty())
            posDir = "../data/INRIAPerson/Train/pos/";

        // Annotations path
        std::cout << "Give the Path for Annotations for Positive " <<
                     "Training Images else press enter (Default is set as " <<
                     "'../data/INRIAPerson/Train/annotations/'): ";
        std::string annotationPath;
        getline(std::cin, annotationPath);
        if (annotationPath.empty())
            annotationPath = "../data/INRIAPerson/Train/annotations/";

        // Negative images path
        std::cout << "Give the Path for Negative "
        "Training Images else press enter" <<
        "(Default is set as '../data/INRIAPerson/Train/neg/'): ";
        std::string negDir;
        getline(std::cin, negDir);
        if (negDir.empty())
            negDir = "../data/INRIAPerson/Train/neg/";

        // Load positive images
        std::cout << "Loading Positive Images" << std::endl;
        detector.loadPosImages(static_cast<cv::String>(annotationPath),
                            static_cast<cv::String>(posDir), windowSize, true);
        // Check if images were successfully loaded
        if (detector.getImgListSize("positive") > 0) {
            std::cout << "Loading Positive Training Data Complete" <<
                                                                    std::endl;
        } else {
            std::cout << "No images found. " <<
                    "Please check the Path Directory: " << posDir << std::endl;
            return 0;
        }

        // load negative images
        std::cout << "Loading Negative Images" << std::endl;
        detector.loadNegImages(static_cast<cv::String>(negDir), windowSize);
        if (detector.getImgListSize("negative") > 0) {
            std::cout << "Loading Negative Training Data Complete" <<
                                                                    std::endl;
        } else {
            std::cout << "No images found. " <<
                    "Please check the Path Directory: " << negDir << std::endl;
            return 0;
        }

        // Start training
        // For Positive Images
        std::cout << "Extracting HOG features and storing in a " <<
                     "vector for Positive Images" << std::endl;
        detector.getHOGfeatures(windowSize, "positive");
        // Assign Positive labels
        size_t positiveCount = detector.getListSize();
        detector.labels.assign(positiveCount, 0);
        std::cout << "Done getting HOG Features for Positive Images" <<
                                                                std::endl;

        // For Negative Images
        std::cout << "Extracting HOG features and storing in a " <<
                     "vector for Negative Images" << std::endl;
        detector.getHOGfeatures(windowSize, "negative");
        // Assign Negative labels
        size_t negativeCount = detector.getListSize() - positiveCount;
        detector.labels.insert(detector.labels.end(), negativeCount, 1);
        std::cout << "Done getting HOG Features for Negative Images" <<
                                                                std::endl;

        // Ask the user if the classifier is to be saved
        std::cout << "Do you want to Save the Trained Classifier? (y/n): ";
        std::string saveClassifier;
        getline(std::cin, saveClassifier);
        std::transform(saveClassifier.begin(), saveClassifier.end(),
                       saveClassifier.begin(), ::tolower);
        if (isEqual(saveClassifier, "yes") || isEqual(saveClassifier, "y")) {
            // Get path for the classifier
            std::cout << "Give the Path for the Location where the " <<
            "Classifier is to be Saved (Default is set as " <<
            "'../data/classifier/svmClassifier'): ";
            std::string svmName;
            getline(std::cin, svmName);
            if (svmName.empty())
                svmName = "../data/classifier/svmClassifier";

            // Start training the SVM classifier
            detector.trainSVM(true, svmName);
        } else if (isEqual(saveClassifier, "no") ||
isEqual(saveClassifier, "n")) {
            // Start training the SVM classifier
            detector.trainSVM(false, "");
        } else {
            std::cout << "Invalid Input" << std::endl;
            return 0;
        }
        std::cout << "Train Demo Finshed" << std::endl;
        std::cout << "The classifier is stored in "
            "../data/classifier/svmClassifier" << std::endl;
    }  else if (isEqual(trainDetector, "no") || isEqual(trainDetector, "n")) {
        // Ask the user if Default classifier is to be used
        std::cout << "Do you want to use OpenCV's Default " <<
                     "People Detector Classifier? (y/n): ";
        std::string defaultClassifier;
        getline(std::cin, defaultClassifier);
        std::transform(defaultClassifier.begin(), defaultClassifier.end(),
                       defaultClassifier.begin(), ::tolower);
        if (defaultClassifier == "yes" || defaultClassifier == "y"
              || defaultClassifier == "Y") {
            // Set directory for Testing Images
            std::cout << "Give the Path for Testing Images or press enter" <<
            "(Default is set as '../data/test/pos/'): ";
            std::string testDir;
            getline(std::cin, testDir);
            if (testDir.empty())
                testDir = "../data/test/pos/";

            // Test Classifier
            cv::Rect r = detector.testClassifier(testDir, cv::Size(),
                                                 true, "Default");
            std::cout << "Test Demo Finshed" << std::endl;
        } else if (isEqual(defaultClassifier, "no") ||
                        isEqual(defaultClassifier, "n")) {
            // Ask the user for the path to the classifier
            std::cout << "If you give a path and that is not valid, default"
            " classifier will be used" << std::endl;
            std::cout << "Give the Path for the Classifier or press "
             "enter to got to recently created classifier" <<
            "(Default is set as '../data/classifier/svmClassifier'): "
             << std::endl;
            std::string tt;
            getline(std::cin, tt);
            std::cout << "From the recently made classifier" << std::endl;

            std::cout << "Give the Path for Testing Images or press enter" <<
            "(Default is set as '../data/test/pos/'): ";
            std::string testDir;
            getline(std::cin, testDir);
            if (testDir.empty())
                testDir = "../data/test/pos/";

            // Test Classifier
            cv::Rect r = detector.testClassifier(testDir, cv::Size(),
                                   true, "Default");



            std::cout << "Test Demo Finshed" << std::endl;
        } else {
            std::cout << "Invalid Input" << std::endl;
            return 0;
        }
    } else {
        std::cout << "Invalid Input" << std::endl;
        return 0;
    }
    return 0;
}

