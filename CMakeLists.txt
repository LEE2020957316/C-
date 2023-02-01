PROJECT (mousecallback)

cmake_minimum_required(VERSION 3.10.0)
set (CMAKE_CXX_STANDARD 11)

SET(SRC_LIST mouse.cpp main.cpp)

ADD_EXECUTABLE(CMouse ${SRC_LIST})
