cmake_minimum_required(VERSION 3.8)
project(Apriori)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp apriori.h functions.h functions.cpp)
add_executable(Apriori ${SOURCE_FILES})