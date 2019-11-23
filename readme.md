# C++ Boilerplate
[![Build Status](https://travis-ci.org/sbrahma0/HUMAN-DETECTION.svg?branch=GMock_extra_credit_sayan_brahma)](https://travis-ci.org/sbrahma0/HUMAN-DETECTION)
[![Coverage Status](https://coveralls.io/repos/github/sbrahma0/HUMAN-DETECTION/badge.svg?branch=GMock_extra_credit_sayan_brahma)](https://coveralls.io/github/sbrahma0/HUMAN-DETECTION?branch=GMock_extra_credit_sayan_brahma)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
---

[Click here to go to the GMock section](#google-mock-test)

## Overview

During catastrophe, natural or man-made, collapsing buildings, landslide or crater is a common phenomenon and many people are deployed to make quick decisions, and try to get victims to safely at their own risk. They must determine the location of victims as quickly as possible so that medics and firefighters can enter the disaster area and save victims. For the last few years, mobile robots have been proposed to help them and to perform tasks that neither humans, dogs nor existing tools can do.

This project should ideally consist of sensors, camera, controls system, and actuators. Sensors should help with speed and obstacle avoidance while maneuvering. The camera should capture frames which will be used in the perception module to detect humans and give position of the human wrt robot. Co-ordinates of the human should be fed to the control system which in turn would actuate the robot to reach the human by continuously adjusting its alignment according to the motion planning module.

For this project, we will be focusing on the perception part of the robot to generate an algorithm to accurately detect and send a location of the human in robot’s frame of reference. Here the robot’s reference point will be considered to be the center pixel of the image and the location of the human will be the central pixel of the bounding box around the human. We would like to generate the location of the human with respect to the robot as the output so that the robot can be given the navigation commands or instructions accordingly. 

We have planned to use the [INRIA Person Dataset](http://pascal.inrialpes.fr/data/human/) for getting the training and testing data and OpenCV library, which is covered under the 3-clause BSD License third party computer vision library for all the image related work with C++ as our coding language. Any other library if required, later on, will be added with permission. We would want the permission to go for any better algorithm apart from the ones decided for the project, which might be easy to implement, if discovered within the duration of the project. 

In the training dataset, by using the HOG features descriptor, which will generate a dense gradient orientation in the localized portion of the image based on occurrence, we will train the SVM classifier to output an optimal hyperplane that will categorize new examples based on the trained ones. After the SVM is being trained, it will be used on the test images to find the accuracy of the model in detecting a human. Finally, using this algorithm we get the location of the human with respect to the robot reference frame. 




## AIP Logs
[AIP Spreadsheet](https://docs.google.com/spreadsheets/d/1HgRF67QFG2dfj0phShHm68qmcLSaLB29Txy_yOnODAY/edit?usp=sharing)- This contains our product backlog, iteration backlog, and work log.
## Sprint doc
[Sprint Planing](https://docs.google.com/document/d/1q1fZa8T8o8WiPjqkdCYfT_voSZSvZKb0-bGTY7lCoBc/edit?usp=sharing) - This contains the google doc with sprint plans and problems faced.


## Dependencies

### UPDATING UBUNTU
```
sudo apt-get update
sudo apt-get upgrade
```
### INSTALL DEPENDENCIES
```
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

sudo apt-get install python3.5-dev python3-numpy libtbb2 libtbb-dev

sudo apt-get install libjpeg-dev libpng-dev libtiff5-dev libjasper-dev libdc1394-22-dev libeigen3-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libavutil-dev libavfilter-dev libavresample-dev
```
### GET OPEN CV

```
git clone https://github.com/opencv/opencv.git
cd opencv 
git checkout 3.3.0 
cd ..
git clone https://github.com/opencv/opencv_contrib.git
cd opencv_contrib
git checkout 3.3.0
cd ..
cd opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \

      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_C_EXAMPLES=ON \
      -D WITH_TBB=ON \
      -D WITH_V4L=ON \
      -D WITH_QT=ON \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_EXAMPLES=ON ..

make -j$(nproc)
sudo make install
sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
sudo ldconfig
```

### CHECKING THE PACKAGE VERSION

```
pkg-config --modversion opencv
```
## OUTPUT DIRECTIONS

### Build
```
git clone --recursive https://github.com/kamakshijain/HUMAN-DETECTION.git
cd <path to repository>
mkdir build
cd build
cmake ..
make
Run program: ./app/shell-app
```
### Demo Walkthrough

Download [INRIA Person Dataset](http://pascal.inrialpes.fr/data/human/) to train our SVM.

Press 'y' if want to train a Classifier. Follow the subsequent steps for a demo on trainning SVM.\
** The program reads data from a default path if a new path isn't given. Press enter to move to next step if you dont want to give a new path.

After trainning demo run -   ./app/shell-app   command to see the testing demo.\ 
Press 'n' to see the testing demo either using your trained SVM or default SVM classifier of opencv.\
** The program reads data from a default path if a new path isnt given. Press enter to move to next step if you dont want to give a new path.

## LICENSE
### Copyright <2019> <Kamakshi Jain> <Sayan Brahma>
```

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```


## Google Mock Test

Google Mock Test is used to test interdependent classes. This way if the base class is changed then the tests for the derived class need not be rewritten.

For this project, Google mock test has been created for class Data. IN other words, class Data has been mocked and class Train has been tested which inherits from class Data. Specifically, in class Train, method readData() calls three methods of class Data. We are testing these methods in the order of their occurence.

Using Google mock macro "EXPECT_CALL", it has been checked that the loadPosImages() method is only called once. Then, it has been checked that getImgListSize() method has been called once with input "positive" and it is called after loadPosImages() method. Then, it has been checked that loadNegImages() method has been called once. At last, it has been checked that getImgListSize() method has been called once with input "negative" and it is called after loadNegImages() method.

Note that, for the Google mock testing, the class dependence is different than the one in master branch. Also note, that a new class has been introduced to the algorithm.The new branch created to implement GMock has not been merged with the master branch. The dataset has also been modified i.e., the images used in this branch are different from the master branch and the extra lines which were written to provide a brief demo, has been removed since the only focus was to implement GMock.

Since this branch is only for GMock implementaton so it is highly recommended to only go through the test conditions and execute the test file by the following steps.
```
git clone --recursive -b GMock_extra_credit_sayan_brahma https://github.com/sbrahma0/HUMAN-DETECTION.git
cd HUMAN-DETECTION
mkdir build
cd build
cmake ..
make
Run program: ./test/cpp-test
```


## Doxygen Documentation

To generate Doxygen Documentation in HTML and LaTEX, follow the next steps:
Create a blank txt file inside a folder docs. 
```
cd <path to repository>
doxygen -g
```
Inside the configuration file, update:
```
PROJECT_NAME = 'your project name'
RECURSIVE = YES
EXCLUDE_PATHS = */VENDOR/*
EXTRACT_ALL = YES
OUTPUT_DIRECTORY       = DOXYGEN/
```
Run and generate the documents by running the next command:
```
doxygen <config_file_name>
```
You can see our complete doxygen file in the path - DOXYGEN/html/index.html

## Final Deliverables
Our deliverables to Acme Robotics would consist of a software package with above defined functionality. The package would consist of the source code, documentation for the source code, documentation for software installation and execution. We will also provide a software demo to demonstrate basic use and functionality.

## Plugins

- CppChEclipse

    To install and run cppcheck in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> cppcheclipse.
    Set cppcheck binary path to "/usr/bin/cppcheck".

    2. To run CPPCheck on a project, right click on the project name in the Project Explorer 
    and choose cppcheck -> Run cppcheck.


- Google C++ Sytle

    To include and use Google C++ Style formatter in Eclipse

    1. In Eclipse, go to Window -> Preferences -> C/C++ -> Code Style -> Formatter. 
    Import [eclipse-cpp-google-style][reference-id-for-eclipse-cpp-google-style] and apply.

    2. To use Google C++ style formatter, right click on the source code or folder in 
    Project Explorer and choose Source -> Format

[reference-id-for-eclipse-cpp-google-style]: https://raw.githubusercontent.com/google/styleguide/gh-pages/eclipse-cpp-google-style.xml

- Git

    It is possible to manage version control through Eclipse and the git plugin, but it typically requires creating another project. If you're interested in this, try it out yourself and contact me on Canvas.
