cmake_minimum_required(VERSION 3.28)
project(Book)

set(CMAKE_CXX_STANDARD 17)

add_executable(Book main.cpp
        BookManagement.h
        interface.h
        BSTree.h
        BookManagement.cpp
        interface.cpp)
