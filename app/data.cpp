/*
 * @file data.cpp
 *
 * Created on: Oct 17, 2019
 * @author: sayan
 * @copyright [2019] Sayan Brahma
 * @brief Implementation of the data class
 */

#include <data.hpp>

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
    std::string line;  // store the lines of each file
    std::string value;  // store the characters of each line
    int j = 0, n = 0;  // Loop through characters and the lines
    char v;

    // Stores the bounding values of the box on an image
    std::vector<int> bbValues;

    // Stores the file name and the directory address of the file
    std::vector<cv::String> filesAnnot, files;
    // Extract files from directories
    cv::glob(anotPath, filesAnnot);
    cv::glob(posDir, files);

    std::cout << "Reading annotations from " << anotPath << std::endl;
    // Main loop for reading through all the files
    // Since range base for loop for 2 variables are difficult to make
    for (auto k = files.begin(), l = filesAnnot.begin();
              k != files.end(), l != filesAnnot.end(); k++, l++) {
        // Stores the file
        std::ifstream inputFile;  // Declare input file with image path
        // Opens all the files starting with the string mentioned
                    // in the filesAnnot.begin
        inputFile.open(*l);
        // Iterate through lines of the file
        int i = 0;
        // Loop continues till the last file in the directory
        while (!inputFile.eof()) {
            getline(inputFile, line);  // Getting individual lines
            // Starting from line 17 with every interval of 7,
            if ((i >= 17) && ((i - 17) % 7 == 0)) {
                // 69th character starts the x,y min and max vales
                j = 69;
                // Start from character num 69 which is first value of Xmin
                v = line[j];
                // Loop continues till the end of the line
                while (j < line.size()) {  // Until end of line
                    if ((v == '(') || (v == ',') || (v == ')') ||
                        (v == ' ') || (v == '-')) {
                        // if these conditions are true,
                        // value is pushed back to bbValues
                        if (n == 0) {
                            bbValues.push_back(stoi(value));
                            // stoi function converts string to integer
                            value.clear();
                        }
                        n++;
                    } else {
                        value += v;  // Append new values
                        // Reset n for a new value
                        n = 0;
                    }
                    j++;
                    v = line[j];  // Read next character
                }
                // Build a rectangle with coordinates -
                                    // xmin,ymin,xmax-xmin,ymax-ymin
                cv::Rect rect(bbValues[0], bbValues[1],
                              bbValues[2] - bbValues[0],
                              bbValues[3] - bbValues[1]);
                // Read the image
                cv::Mat img = cv::imread(*k);
                // Check if the image is empty
                if (img.empty()) {
                    std::cout << *k << " is invalid!" << std::endl;
                    continue;
                }
                // Extract the human as per the annotations
                img = img(rect);
                // Resize the image to make all images of the same size
                cv::resize(img, img, size);
                // Display loaded images, if asked
                if (dispImg) {
                    cv::imshow("Positive Images", img);
                    cv::waitKey(10);
                }
                // Store the images in a list
                posImgList.push_back(img);
                // Clear bbValues before extracting next rectangle
                bbValues.clear();
           }
           i++;  // Next line
        }
        inputFile.close();
    }
}

/**
 * @brief This function loads the negative images from the training dataset
 * @param dirName The name of the directory
 * @param size The size of the window of the images for sample
 */
void Data::loadNegImages(const cv::String dirName, const cv::Size size) {
    // Store files names
    std::vector<cv::String> files;
    // Extract file from the directory
    cv::glob(dirName, files);

    // Define a box of the same size as given
    cv::Rect box;
    box.width = size.width;
    box.height = size.height;
    const int size_x = box.width;
    const int size_y = box.height;

    // Random number seed
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    srand(seed);

    // Read Negative Images
    for (auto imgName : files) {
        // Read the image
        cv::Mat img = cv::imread(imgName);
        // Check if image was read
        if (img.empty()) {
            std::cout << imgName << " is invalid!" << std::endl;
            continue;
        }

        // Create a box randomly on the negative images
        box.x = rand_r(&seed) % (img.cols - size_x);
        box.y = rand_r(&seed) % (img.rows - size_y);
        img = img(box);
        // Store the image in a list
        negImgList.push_back(img);
    }
}

/*
 * @brief This is the destructor for the class
 */
Data::~Data() {
    std::cout << "Class Data has been Destroyed" << std::endl;
}
