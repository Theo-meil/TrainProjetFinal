﻿cmake_minimum_required(VERSION 3.0)
project(TrainProjetvfinal)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(TrainProjetvfinal "main.cpp"  "train.cpp"  "urgenceControl.cpp" "station.cpp" ) 


target_link_libraries(TrainProjetvfinal sfml-graphics sfml-window sfml-system)

