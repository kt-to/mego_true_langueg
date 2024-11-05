//
// Created by Дмитрий Фоминых on 24.10.2024.
//
#include "bor.h"

int bor::gagago(std::string &word, int i) {
    auto now = _start;
    while (i != word.size()) {
        bool cont = false;
        for (auto& to : now->chils) {
            if (to->sim == word[i]) {
                cont = true;
                now = to;
                i++;
                break;
            }
        }
        if (!cont) {
            return 0;
        }
    }
    if (now->is_key_word) {
        return 1;
    }
    if (now->is_operator) {
        return 2;
    }
    return 0;
}


bor::bor() {
    _start = new node();
    _cnt_words = 0;
}

void bor::add(std::string &word, int type) {
    int i = 0;
    auto now = _start;
    bool cont = false;
    while (i != word.size()) {
        cont = false;
        for (auto& to : now->chils) {
            if (to->sim == word[i]) {
                cont = true;
                now = to;
                i++;
                break;
            }
        }
        if (!cont) {
            auto br = new node(word[i]);
            i++;
            now->chils.push_back(br);
            now = br;
        }
    }
    if (type == 1) {
        now->is_key_word = true;
    }
    if (type == 2) {
        now->is_operator = true;
    }
    ++_cnt_words;
}

bor::node::node() {
    sim = '\0';
    is_operator = false;
    is_key_word = false;
}

bor::node::node(char _sim) {
    sim = _sim;
    is_key_word = false;
    is_operator = false;
}

int bor::get_cnt_words() {
    return _cnt_words;
}