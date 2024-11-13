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
    return now->type;
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
    ++_cnt_words;
    now->type = type;
}

bor::node::node() {
    sim = '\0';
}

bor::node::node(char _sim) {
    sim = _sim;
}

int bor::get_cnt_words() {
    return _cnt_words;
}