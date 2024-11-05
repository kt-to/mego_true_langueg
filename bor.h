//
// Created by Дмитрий Фоминых on 24.10.2024.
//

#ifndef MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H
#define MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H

#endif //MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H

#pragma once
#include "vector"
#include "string"

class bor {
public:
    bor();

    int gagago(std::string& word, int i = 0);
    // 0 ничего
    // 1 key_word
    // 2 operator
    // 3 number
    // 4 comment
    // 5 literal
    // 6 double
    void add(std::string& word, int type);

    int get_cnt_words();
private:
    struct node {
        node();
        node(char sim);
        char sim;
        std::vector<node*> chils;
        bool is_operator;
        bool is_key_word;
    };
    node* _start;
    int _cnt_words;
};