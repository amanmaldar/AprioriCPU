cmake_minimum_required(VERSION 3.8)
project(Apriori)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        apriori.cpp
        apriori.hcu
        functions.hcu
        )

add_executable(Apriori ${SOURCE_FILES})