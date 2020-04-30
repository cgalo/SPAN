cmake_minimum_required(VERSION 3.15)
project(SPAN)

set(CMAKE_CXX_STANDARD 14)

add_executable(SPAN main.cpp LinkedList/LinkedList.cpp LinkedList/LinkedList.h MinHeap/MinHeap.cpp MinHeap/MinHeap.h)