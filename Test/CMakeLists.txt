#setting cmake version and project name
cmake_minimum_required(VERSION 3.6)
project(GevProgRoadFighter)

set(CMAKE_CXX_STANDARD 14)

#pthread flag is needed to make gtest run on linux
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_EXE_LINKER_FLAGS -pthread)

#set include dir for gtest
include_directories(../gtest/include)
# Set Library dir for gtest
link_directories(../gtest/lib)

# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../cmake/Modules")

#making a debug targer to link gtest to
SET(SRC mainTest.cpp
        EntityTests.cpp
        OberserTests.cpp
        HighScoreTests.cpp
        InputTests.cpp)

# adding a test executable to test he library
ADD_EXECUTABLE(GevProgRoadFighterTest ${SRC})

#linking ggl and gtest to debug targer
TARGET_LINK_LIBRARIES(GevProgRoadFighterTest LINK_PUBLIC GLL gtest)

INSTALL(TARGETS GevProgRoadFighterTest DESTINATION ${PROJECT_SOURCE_DIR}/bin)