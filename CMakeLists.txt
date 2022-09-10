cmake_minimum_required(VERSION 3.23)
project(ED2_Rework)

set(CMAKE_CXX_STANDARD 20)

add_executable(ED2_Rework src/main.cpp src/Review.cpp src/Review.h src/CsvFile.cpp src/CsvFile.h src/File.h src/File.cpp src/BinFile.cpp src/BinFile.h)
