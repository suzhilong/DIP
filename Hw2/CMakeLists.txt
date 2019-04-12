cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(img_rotate)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER "g++")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_BUILD_TYPE debug)

set(OpenCV_DIR /usr/local/share/OpenCV)
find_package(OpenCV REQUIRED )
FIND_PACKAGE( Boost 1.40 COMPONENTS program_options filesystem REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
include_directories( ${OPENCV_INCLUDE_DIR} )

add_executable (image_rotate  image_rotate.cpp)
target_link_libraries (image_rotate ${OpenCV_LIBS})
