
/*
 * @file train.cpp
 *
 * Created on: Oct 17, 2019
 * @author: sayan
 * @copyright [2019] Sayan Brahma
 * @brief Train class implementation for training the SVM parameters using HOG descriptors
 */
#include <train.hpp>

/*
 * @brief This is the constructor for the class
 */
Train::Train() {
    // Initialize classifier
    classifier = cv::ml::SVM::create();
    // Default values to train SVM
    classifier->setCoef0(0.0);
    classifier->setDegree(3);
    classifier->setTermCriteria(cv::TermCriteria(
    cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 1000, 1e-3));
    classifier->setGamma(0);
    classifier->setKernel(cv::ml::SVM::LINEAR);
    classifier->setNu(0.5);
    classifier->setP(0.1);  // for EPSILON_SVR, epsilon in loss function?
    classifier->setC(0.01);  // From paper, soft classifier
    classifier->setType(cv::ml::SVM::EPS_SVR);
    std::cout << "Class Train has been Initialized" << std::endl;
}

/*
 * @brief This function outputs the support vectors of the classifier.
 * @return A double vector containing the support vectors.
 */
std::vector<float> Train::getClassifier() {
    // get the support vectors
    cv::Mat svm = classifier->getSupportVectors();
    // get the decision function
    cv::Mat alpha, svidx;
    double rho = classifier->getDecisionFunction(0, alpha, svidx);
    // create a variable to return the support vectors in desired type
    std::vector<float> hogDetector(svm.cols + 1);
    memcpy(&hogDetector[0], svm.ptr(), svm.cols*sizeof(hogDetector[0]));
    hogDetector[svm.cols] = static_cast<float>(- rho);
    return hogDetector;
}
/*
 * @brief This function extracts HOG descriptors from an image
 * @param It is the window size used for HOG feature extraction
 * @param Vector containing the images whose features need to be extracted
 */
void Train::getHOGfeatures(const cv::Size windowSize,
                           const std::vector<cv::Mat> & imgList) {
    cv::HOGDescriptor hog;
    hog.winSize = windowSize;
    hog.cellSize = cv::Size(4, 4);
    cv::Mat gray;
    std::vector<float> descriptors;
    for (auto data : imgList)
        if (data.cols >= windowSize.width && data.rows >= windowSize.height) {
            // convert image to grayscale
            cvtColor(data, gray, cv::COLOR_BGR2GRAY);
            // extract hog features
            hog.compute(gray, descriptors);
            // store hog features
            gradientList.push_back(cv::Mat(descriptors).clone());
            // flip the images
            cv::flip(gray, gray, 1);
            hog.compute(gray, descriptors);
            gradientList.push_back(cv::Mat(descriptors).clone());
        }
}

/**
 * @brief This function trains the SVM Classifier
 * @param saveClassifier Whether to save the trained classifier or not
 * @param classifierName Name of the classifer to be saved
 */
void Train::trainSVM(const bool saveClassifier = false,
                     const cv::String classifierName = "") {
    // check if HOG features are row vectors
    const int rows = static_cast<int>(gradientList.size());
    const int cols = static_cast<int>(std::max(gradientList[0].cols,
                                               gradientList[0].rows));
    cv::Mat temp(1, cols, CV_32FC1), trainData(rows, cols, CV_32FC1);
    // auto index = 0;
    for (auto index = 0; index < gradientList.size(); index++) {
        if (gradientList[index].cols == 1) {
            transpose(gradientList[index], temp);
            temp.copyTo(trainData.row(static_cast<int>(index)));
        } else if (gradientList[index].rows == 1) {
            gradientList[index].copyTo(trainData.row(static_cast<int>(index)));
        }
    }

    // Training Starts
    std::cout << "Training SVM Classifier" << std::endl;
    classifier->train(trainData, cv::ml::ROW_SAMPLE, labels);
    std::cout << "Training Finshed" << std::endl;
    // Save the classifier if asked
    if (saveClassifier)
        classifier->save(classifierName);
}
/**
 * @brief Destructor of the train class
 */
Train::~Train() {
    std::cout << "Class Train has been Destroyed" << std::endl;
}

