cmake_minimum_required(VERSION 2.8)
project(capture_motion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS} -std=c++11 -Wall -Wextra -pedantic -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(EXECUTABLE capture_motion.out)

# find packages
find_package(OpenCV REQUIRED)

set(PROJECT_INCLUDE_DIRS ${OpenCV_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_LIBRARIES ${OpenCV_LIBRARIES})

include_directories(${PROJECT_INCLUDE_DIRS})
add_executable(${EXECUTABLE} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE} ${PROJECT_LIBRARIES})
