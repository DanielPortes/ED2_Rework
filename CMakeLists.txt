cmake_minimum_required(VERSION 3.23)


project(ED2_Rework)


set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(ED2_Rework
        src/BinFile.cpp
        src/BinFile.h
        src/CsvFile.cpp
        src/CsvFile.h
        src/File.cpp
        src/File.h
        src/main.cpp
        src/Review.cpp
        src/Review.h
        src/Tester.cpp
        src/Tester.h
        src/Sort.cpp
        src/Sort.h
        src/Hash.cpp
        src/Hash.h
        src/RedBlackTree.cpp
        src/RedBlackTree.h
        src/BTree.cpp
        src/BTree.h
        src/HuffmanCompressor.cpp
        src/HuffmanCompressor.h
)
