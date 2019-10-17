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
 * @brief Constructor for the class; Initialisation
 */
Train::Train() {
    //  Initialize classifier
    classifier = cv::ml::SVM::create();
    // values to train svm
    classifier->setCoef0(0.0);
    classifier->setDegree(3);
    classifier->setTermCriteria(cv::TermCriteria(
    cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 1000, 1e-3));
    classifier->setGamma(0.0);
    classifier->setKernel(cv::ml::SVM::LINEAR);
    classifier->setNu(0.5);
    classifier->setP(0.1);  // for EPSILON_SVR
    classifier->setC(0.01);  //  soft classifier
    classifier->setType(cv::ml::SVM::EPS_SVR);
}
