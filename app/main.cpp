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
            // Start training

            Train trainClass;

            // For Positive Images
            std::cout << "Extracting HOG descriptors and storing ir in a " <<
                         "vector for Positive Images" << std::endl;
            trainClass.GetHogFeatures(windowSize, allData.posImageList);
            // Assign Positive labels
            size_t positiveCount = trainClass.gradList.size();
            trainClass.labels.assign(positiveCount, 0);
            std::cout << "Extracted HOG Descriptors for Positive Images" <<
                                                                    std::endl;

            // For negative images
            std::cout << "Extracting HOG descriptors and storing ir in a " <<
                         "vector for negative Images" << std::endl;
            trainClass.GetHogFeatures(windowSize, allData.negImageList);
            // Assign Negative labels
            size_t negativeCount = trainClass.gradList.size() - positiveCount;
            trainClass.labels.insert(trainClass.labels.end(), negativeCount, 1);
            std::cout << "Extracted HOG Descriptors for Positive Images" <<
            std::endl;

            // Choice of saving the classifier
            std::cout << "Save the Trained Classifier? (y/n): ";
            std::string saveClassifier;
            getline(std::cin, saveClassifier);
            std::transform(saveClassifier.begin(), saveClassifier.end(),
                           saveClassifier.begin(), ::tolower);
            if (saveClassifier == "yes" || saveClassifier == "y"
            || saveClassifier == "Y") {
                // Get path for the classifier
                std::cout << "Give the Path for the Location where the " <<
                "Classifier is to be Saved (Default is set as " <<
                "'../data/classifier/svmClassifier'): ";
                std::string svmName;
                getline(std::cin, svmName);
                if (svmName.empty())
                    svmName = "../data/classifier/svmClassifier";

                // Start training the SVM classifier
                trainClass.TrainSVM(true, svmName);
            } else if (saveClassifier == "no" || saveClassifier == "n") {
                // Start training the SVM classifier
                trainClass.TrainSVM(false, "");
            } else {
                std::cout << "Invalid Input" << std::endl;
                return 0;
            }

            // Setting path for test images
            std::cout << "Give the Testing Images address else press"
            " enter to use the default one- ";
            std::string testDir;
            getline(std::cin, testDir);
            if (testDir.empty())
                testDir = "../data/INRIAPerson/Test/pos/";

            // Test classifier
            Detect detector;
            detector.hogUser.winSize = windowSize;
            detector.hogUser.cellSize = cv::Size(4, 4);
            detector.hogUser.setSVMDetector(trainClass.GetClassifier());
            cv::Rect r = detector.TestClassifier(
                static_cast<cv::String>(testDir), windowSize, "User");
            std::cout << "Program Finished" << std::endl;
        } else if (trainDetector == "no" || trainDetector == "n") {
            // Ask the user if Default classifier is to be used
            std::cout << "Do you want to use OpenCV's Default " <<
                         "human Detector Classifier? (y/n): ";
            std::string defaultClassifier;
            getline(std::cin, defaultClassifier);
            std::transform(defaultClassifier.begin(), defaultClassifier.end(),
                           defaultClassifier.begin(), ::tolower);
            if (defaultClassifier == "yes" || defaultClassifier == "y") {
                // Set directory for Testing Images
                std::cout << "Give the Path for Testing Images " <<
                "(Default is set as '../data/test/pos/'): ";
                std::string testDir;
                getline(std::cin, testDir);
                if (testDir.empty())
                    testDir = "../data/test/pos/";

                // Test Classifier
                Detect detector;
                cv::Rect r = detector.TestClassifier(testDir, cv::Size(),
                                                     "Default");
                std::cout << "Finished" << std::endl;
            } else if (defaultClassifier == "no" || defaultClassifier == "n") {
                // Ask the user for the path to the classifier
                std::cout << "Give the Path for the Classifier " <<
                "(Default is set as '../data/classifier/svmClassifier'): ";
                std::string svmName;
                getline(std::cin, svmName);
                if (svmName.empty())
                    svmName = "../data/classifier/svmClassifier";

                // Initialize the classifier
                Train trainClass;
                trainClass.classifier = cv::ml::SVM::load(svmName);

                // Set path for Testing Images
                std::cout << "Give the Path for Testing Images " <<
                "(Default is set as '../data/test/pos/'): ";
                std::string testDir;
                getline(std::cin, testDir);
                if (testDir.empty())
                    testDir = "../data/test/pos/";

                // Test Classifier
                Detect detector;
                detector.hogUser.winSize = windowSize;
                detector.hogUser.cellSize = cv::Size(4, 4);
                detector.hogUser.setSVMDetector(trainClass.GetClassifier());
                cv::Rect r = detector.TestClassifier(testDir, windowSize,
                                                     "User");
                std::cout << "Finished" << std::endl;
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
