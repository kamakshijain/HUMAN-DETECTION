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
 * @file train.cpp
 *
 * Created on: Oct 17, 2019
 * @author: sayan
 * @copyright [2019] Sayan Brahma
 * @brief Train class implementation for training the SVM parameters using HOG descriptors
 */

#include "train.hpp"

/*
 * This is the constructor for the class
 */
Train::Train(Data & _allData)
    : allData(_allData) {
  // Initialize classifier
  classifier = cv::ml::SVM::create();
  // Default values to train SVM
  classifier->setCoef0(0.0);
  classifier->setDegree(3);
  classifier->setTermCriteria(
      cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 1000,
                       1e-3));
  classifier->setGamma(0);
  classifier->setKernel(cv::ml::SVM::LINEAR);
  classifier->setNu(0.5);
  classifier->setP(0.1);  // for EPSILON_SVR, epsilon in loss function?
  classifier->setC(0.01);  // From paper, soft classifier
  classifier->setType(cv::ml::SVM::EPS_SVR);
  std::cout << "Class Train has been Initialized" << std::endl;
}

/*
 * This is the first method of the class. It outputs the support vectors of the
 * classifier.
 */
std::vector<float> Train::getClassifier() {
  // get the support vectors
  cv::Mat svm = classifier->getSupportVectors();
  // get the decision function
  cv::Mat alpha, svidx;
  double rho = classifier->getDecisionFunction(0, alpha, svidx);

  // create a variable to return the support vectors in desired type
  std::vector<float> hogDetector(svm.cols + 1);
  memcpy(&hogDetector[0], svm.ptr(), svm.cols * sizeof(hogDetector[0]));
  hogDetector[svm.cols] = static_cast<float>(-rho);
  return hogDetector;
}

/*
 * This is the second method of the class. It extracts HOG features from the
 * given images.
 */
void Train::getHOGfeatures(const cv::Size windowSize,
                           const std::string & imgType) {
  cv::HOGDescriptor hog;
  hog.winSize = windowSize;
  hog.cellSize = cv::Size(4, 4);
  cv::Mat gray;
  std::vector<float> descriptors;

  std::vector < cv::Mat > imgList = allData.getImgList(imgType);
  for (auto data : imgList)
    if (data.cols >= windowSize.width && data.rows >= windowSize.height) {
      // convert image to grayscale
      cvtColor(data, gray, cv::COLOR_BGR2GRAY);
      // extract hog features
      hog.compute(gray, descriptors);
      // store hog features
      gradientList.push_back(cv::Mat(descriptors).clone());
      // Now flip the images
      cv::flip(gray, gray, 1);
      hog.compute(gray, descriptors);
      gradientList.push_back(cv::Mat(descriptors).clone());
    }
}

/*
 * This is the third method of the class. It trains the SVM classifier.
 */
void Train::trainSVM(const bool saveClassifier = false,
                     const cv::String classifierName = "") {
  // make sure all HOG features are row vectors for the train function of SVM
  const int rows = static_cast<int>(gradientList.size());
  const int cols = static_cast<int>(std::max(gradientList[0].cols,
                                             gradientList[0].rows));
  cv::Mat temp(1, cols, CV_32FC1), trainData(rows, cols, CV_32FC1);
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

/*
 * This is the fourth method of the class. It gives the size of the gradient
 * list.
 */
int Train::getListSize() {
  return gradientList.size();
}

/*
 * This is the fifth method of the class. It sets the classifier for the class.
 */
void Train::setClassifier(const cv::Ptr<cv::ml::SVM> userClassifier) {
  classifier = userClassifier;
}

/*
 * This is the sixth method of the class. It returns the classifier for the
 * class.
 */
cv::Ptr<cv::ml::SVM> Train::getDefaultClassifier() {
  return classifier;
}

/*
 * This is the seventh method of the class. It reads all the data.
 */
bool Train::readData(const cv::String anotPath, const cv::String posDir,
                     const cv::String negDir, const cv::Size size,
                     const bool dispImg = false) {
  bool state = true;
  // Load positive images
  if ((!anotPath.empty()) & (!posDir.empty())) {
    std::cout << "Loading Positive Images" << std::endl;
    allData.loadPosImages(anotPath, posDir, size, dispImg);
    // Check if images were successfully loaded
    if (allData.getImgListSize("positive") > 0) {
      std::cout << "Loading Positive Images Complete" << std::endl;
    } else {
      std::cout << "No images found. " << "Please check the Path Directory: "
          << posDir << std::endl;
      state = false;
    }
  }

  // Now load negative images
  if (!negDir.empty()) {
    std::cout << "Loading Negative Images" << std::endl;
    allData.loadNegImages(negDir, size);
    if (allData.getImgListSize("negative") > 0) {
      std::cout << "Loading Negative Images Complete" << std::endl;
    } else {
      std::cout << "No images found. " << "Please check the Path Directory: "
          << negDir << std::endl;
      state = false;
    }
  }
  return state;
}

/*
 * This is the destructor for the class
 */
Train::~Train() {
  std::cout << "Class Train has been Destroyed" << std::endl;
}

