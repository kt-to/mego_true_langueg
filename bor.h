//
// Created by Дмитрий Фоминых on 24.10.2024.
//

#ifndef MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H
#define MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H

#endif //MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H

#include "vector"
#include "string"

class bor {
public:
    bor();

    int gagago(std::string& word, int i = 0);
    // 0 нечего
    // 1 key_word
    // 2 opperator
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