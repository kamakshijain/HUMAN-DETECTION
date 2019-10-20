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
    if (trainDetector == "yes" || trainDetector == "y"
            || trainDetector == "Y") {
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
        Data allData;
        std::cout << "Loading Positive Images" << std::endl;
        allData.loadPosImages(static_cast<cv::String>(annotationPath),
                            static_cast<cv::String>(posDir), windowSize, true);
        // Check if images were successfully loaded
        if (allData.getPosImgList().size() > 0) {
            std::cout << "Loading Positive Training Data Complete" << std::endl;
        } else {
            std::cout << "No images found. " <<
                    "Please check the Path Directory: " << posDir << std::endl;
            return 0;
        }

        // load negative images
        std::cout << "Loading Negative Images" << std::endl;
        allData.loadNegImages(static_cast<cv::String>(negDir), windowSize);
        if (allData.getNegImgList().size() > 0) {
            std::cout << "Loading Negative Training Data Complete" << std::endl;
        } else {
            std::cout << "No images found. " <<
                    "Please check the Path Directory: " << negDir << std::endl;
            return 0;
        }

        // Start training
        Train trainClass;
        // For Positive Images
        std::cout << "Extracting HOG features and storing in a " <<
                     "vector for Positive Images" << std::endl;
        trainClass.getHOGfeatures(windowSize, allData.getPosImgList());
        // Assign Positive labels
        size_t positiveCount = trainClass.getGradientList().size();
        trainClass.labels.assign(positiveCount, 0);
        std::cout << "Done getting HOG Features for Positive Images" <<
                                                                std::endl;

        // For Negative Images
        std::cout << "Extracting HOG features and storing in a " <<
                     "vector for Negative Images" << std::endl;
        trainClass.getHOGfeatures(windowSize, allData.getNegImgList());
        // Assign Negative labels
    size_t negativeCount = trainClass.getGradientList().size() - positiveCount;
        trainClass.labels.insert(trainClass.labels.end(), negativeCount, 1);
        std::cout << "Done getting HOG Features for Negative Images" <<
                                                                std::endl;

        // Ask the user if the classifier is to be saved
        std::cout << "Do you want to Save the Trained Classifier? (y/n): ";
        std::string saveClassifier;
        getline(std::cin, saveClassifier);
        std::transform(saveClassifier.begin(), saveClassifier.end(),
                       saveClassifier.begin(), ::tolower);
        if (saveClassifier == "yes" || saveClassifier == "y") {
            // Get path for the classifier
            std::cout << "Give the Path for the Location where the " <<
            "Classifier is to be Saved (Default is set as " <<
            "'../data/classifier/svmClassifier'): ";
            std::string svmName;
            getline(std::cin, svmName);
            if (svmName.empty())
                svmName = "../data/classifier/svmClassifier";

            // Start training the SVM classifier
            trainClass.trainSVM(true, svmName);
        } else if (saveClassifier == "no" || saveClassifier == "n") {
            // Start training the SVM classifier
            trainClass.trainSVM(false, "");
        } else {
            std::cout << "Invalid Input" << std::endl;
            return 0;
        }
        std::cout << "Train Demo Finshed" << std::endl;
        std::cout << "The classifier is stored in "
            "../data/classifier/svmClassifier" << std::endl;
    } else if (trainDetector == "no" || trainDetector == "n"
          || trainDetector == "N") {
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
            Detect detector;
            cv::Rect r = detector.testClassifier(testDir, cv::Size(),
                                                 true, "Default");
            std::cout << "Test Demo Finshed" << std::endl;
        } else if (defaultClassifier == "no" || defaultClassifier == "n"
             || defaultClassifier == "N") {
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
            Detect detector;
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
