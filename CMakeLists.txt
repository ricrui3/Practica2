cmake_minimum_required(VERSION 3.2)
project(Practica2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ExpresionRegular.txt)
add_executable(Practica2 ${SOURCE_FILES} AFN.hpp)