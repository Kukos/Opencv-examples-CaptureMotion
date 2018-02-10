# Opencv examples: Capture Motion

This is example how to use opencv C++ framework to detect and capture motion.

### Description
This program works as follow:
1. Read frames from webcam
2. Detect motion in base of substraction frames
3. Capture motion frame to file

### Setup

You have to install opencv, or if you have OS based on Debian like Ubuntu,

just run ./scripts/opencv_install.sh

### How to build
mkdir build && cd build && cmake \.\. && make
