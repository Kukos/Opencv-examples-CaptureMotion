#!/bin/bash

#Script for install openCV

#Author Michal Kukowski
#email: michalkukowski10@gmail.com

this_dir="`pwd`"
temp_dir = "$this_dir"/temp
opencv_modules_dir="$temp_dir"/opencv_contrib

#Download OpenCV
mkdir $temp_dir
cd $temp_dir
git clone https://github.com/opencv/opencv_contrib.git
git clone https://github.com/opencv/opencv.git

#Build OpenCV
cd opencv
mkdir ./build
cd ./build
cmake -D CMAKE_BUILD_TYPE=RELEASE -DOPENCV_EXTRA_MODULES_PATH="$opencv_modules_dir"/modules -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j `nproc`

#Install
sudo make install

#Clean
cd "$this_dir"
rm -rf  "$temp_dir"
