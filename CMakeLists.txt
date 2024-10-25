cmake_minimum_required(VERSION 3.28)
project(mego_true_langueg)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mego_true_langueg
        bor.cpp
        bor_for_kay.h
        main.cpp
        analizun.cpp
        Lexeme.h
        Lexeme.cpp)
