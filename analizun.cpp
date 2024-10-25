#include "bits/stdc++.h"
#include "Lexeme.h"
#include "bor.h"

using namespace std;

bor b;

void add(string& s, vector<Lexeme>& res) {
    if (s.empty()) return;
    res.push_back({b.gagago(s), s});
    if (res.back().type == 0 && isdigit(res.back().data[0])) {
        throw "EMAE";
    }
    s.clear();
}

void addop(string& s, vector<Lexeme>& res) {
    if (s.empty()) return;
    string cur;
    for (auto& c : s) {
        cur.push_back(c);
        if (b.gagago(cur)) {
            res.push_back({b.gagago(cur), cur});
            cur.clear();
        }
    }
    s.clear();
}

map<char, int> is_operator{{'!', 1}, {'^', 1}, {'&', 1}, {'|', 1}, {'+', 1},
{'-', 1}, {'%', 1}, {'/', 1}, {'*', 1}, {'=', 1}, {'<', 1}, {'>', 1}, {'(', 1},
{')', 1}, {'[', 1}, {']', 1}, {'{', 1}, {'}', 1}};

// 0 - nothing
// 1 - number
// 2 - word
// 3 - operator

vector<Lexeme> lepsikon(const string& s) {
    vector<Lexeme> res;
    string cur;
    cur.push_back(' ');
    int cond = 0;
    for (auto& c : s) {
        if (c == ' ' || c == '\n') {
            if (cur.empty()) continue;
            if (cond == 3) {
                addop(cur, res);
            } else {
                add(cur, res);
            }
            cond = 0;
        } else if (is_operator[c]) {
            if (cond != 3) {
                add(cur, res);
            }
            cond = 3;
            cur.push_back(c);
        } else if (cond == 0) {
            if (isdigit(c)) {
                cond = 1;
            } else if (isalpha(c) || c == '_') {
                cond = 2;
            }
            cur.push_back(c);
        } else if (cond == 1) {
            if (!isdigit(c)) {
                throw "EMAE";
            }
            cur.push_back(c);
        } else if (cond == 2) {
            cur.push_back(c);
        } else {
            addop(cur, res);
            cur.push_back(c);
            cond = isdigit(c) ? 1 : 2;
        }
    }
    return res;
}
