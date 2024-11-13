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

    void add(std::string& word, int type);

    int get_cnt_words();
private:
    struct node {
        node();
        node(char sim);
        char sim;
        std::vector<node*> chils;
        int type;
    };
    node* _start;
    int _cnt_words;
};