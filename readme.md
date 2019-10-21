# C++ Boilerplate
[![Build Status](https://travis-ci.org/kamakshijain/HUMAN-DETECTION.svg?branch=master)](https://travis-ci.org/kamakshijain/HUMAN-DETECTION)
[![Coverage Status](https://coveralls.io/repos/github/kamakshijain/HUMAN-DETECTION/badge.svg?branch=master)](https://coveralls.io/github/kamakshijain/HUMAN-DETECTION?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---

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




## Building for code coverage (for assignments beginning in Week 4)
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Working with Eclipse IDE ##

## Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/kamakshijain/HUMAN-DETECTION.git
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of cpp-boilerplate

```
cd ~/workspace
mkdir -p boilerplate-eclipse
cd boilerplate-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../cpp-boilerplate/
```

## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "boilerplate-eclipse" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold boilerplate-eclipse project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

## Run

1. In Eclipse, right click on the boilerplate-eclipse in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (e.g. shell-app, cpp-test for unit testing)


## Debug


1. Set breakpoint in source file (i.e. double click in the left margin on the line you want 
the program to break).

2. In Eclipse, right click on the boilerplate-eclipse in Project Explorer, select Debug As -> 
Local C/C++ Application, choose the binaries to run (e.g. shell-app).

3. If prompt to "Confirm Perspective Switch", select yes.

4. Program will break at the breakpoint you set.

5. Press Step Into (F5), Step Over (F6), Step Return (F7) to step/debug your program.

6. Right click on the variable in editor to add watch expression to watch the variable in 
debugger window.

7. Press Terminate icon to terminate debugging and press C/C++ icon to switch back to C/C++ 
perspetive view (or Windows->Perspective->Open Perspective->C/C++).


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
