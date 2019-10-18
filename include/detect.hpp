/**
 * @author kamakshi jain
 * @file detect.hpp
 * @copyright [2019] kamakshi jain
 * @brief This is the stub for the detect class
 */

#ifndef INCLUDE_DETECT_HPP_
#define INCLUDE_DETECT_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

class Detect {
/**
 * @brief Public methods declaration
 */
 public:
	/**
	 * @brief Constructor of the class Detect
	 */
    Detect();
    /**
     * @brief This function toggles between the Default mode and User mode.
     */
    void SwitchMode();
    /**
     * @brief This function returns the current working mode
     * @return The working mode in string type
     */
    std::string GetMode() const;
    /**
     * @brief This function provides a bounding box around the humans detected
     * @param The image on which human is to be detected
     * @return A vector containing the coordinates bounding box
     */
    std::vector<cv::Rect> DetectHumans(const cv::InputArray);
    /**
     * @brief This functions adjusts the bounding box around the humans
     * @param The bounding box detected from the detectHumans finction
     */
    void AdjustBoundingBox(cv::Rect &);
    /**
     * @brief This function gives the direction where the robot should go for extraction
     * @param The image where the humans are detected
     * @param The adjusted bounding box around humans
     * @return The direction in string format
     */
    std::string Direction(const cv::InputArray, cv::Rect &);
    /**
     * @brief This function is used to test the trained classifier
     * @param directory address of the test set
     * @param image size of the testing image
     * @param mode of testing the classifier
     * @return Coordinates the bounding box based on the test results
     */
    cv::Rect TestClassifier(const cv::String,
            const cv::Size, const std::string &);
    /**
     * @brief Destructor of the Detect class
     */
    ~Detect();

	cv::HOGDescriptor& getHogUser() {
		return hogUser;
	}

	void setHogUser(const cv::HOGDescriptor &hogUser) {
		this->hogUser = hogUser;
	}

	cv::HOGDescriptor& getHogDefault() {
		return hogDefault;
	}

	void setHogDefault(const cv::HOGDescriptor &hogDefault) {
		this->hogDefault = hogDefault;
	}

/**
 * @private variable declaration
 */
 private:
    enum mode {Default, User} m;
    // since c++ 11 - enum name : type ;
    cv::HOGDescriptor hogDefault, hogUser;
};

#endif  // INCLUDE_DETECT_HPP_

