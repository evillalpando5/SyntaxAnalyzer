cmake_minimum_required(VERSION 3.30)
project(lexAnalyzer)

set(CMAKE_CXX_STANDARD 20)

add_executable(lexAnalyzer main.cpp
        SyntaxAnalyzer.h
        SyntaxAnalyzer.cpp
)
