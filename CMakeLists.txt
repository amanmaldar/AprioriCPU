cmake_minimum_required(VERSION 3.8)
project(Apriori)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        apriori.cu
        apriori.h
        apriori.hcu
        functions.h
        functions.hcu
        main.cpp)

add_executable(Apriori ${SOURCE_FILES})