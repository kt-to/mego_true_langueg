cmake_minimum_required(VERSION 3.25)
project(mego_true_langueg)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mego_true_langueg
        bor.cpp
        lexicon.cpp
    Lexeme.cpp
        Lexer.h
        lexer_exp.h
        Lexer.cpp
        lexer_exp.cpp
        lexicon.h
        main.cpp
        semanter.cpp
        semanter.h
        semanter.cpp
        TID.h
        TID.cpp
        sem_stack.h
        sem_stack.cpp
        poliz.cpp
        poliz.h)
