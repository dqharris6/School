cmake_minimum_required(VERSION 3.4)
project(315quiz)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    q4.c q5.cpp q5.h)

add_executable(315quiz ${SOURCE_FILES})