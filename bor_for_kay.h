//
// Created by Дмитрий Фоминых on 24.10.2024.
//

#ifndef MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H
#define MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H

#endif //MEGO_TRUE_LANGUEG_BOR_FOR_KAY_H

#include "vector"
#include "string"

class bor() {
public:
    int gagago(std::string& word);
    // 0 нечего
    // 1 key_word
    // 2 opperator
private:
    struct node {
        std::vector<node*> chils;
        bool _operator;
        bool _key_word;
    };
    void build();
    void add(std::string& word);
    node* _start;

}