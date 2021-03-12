cmake_minimum_required(VERSION 3.5.1)

project(Print_Backtrace)

include_directories("../../../cpp/debug")

add_executable(backtrace main.cpp)

