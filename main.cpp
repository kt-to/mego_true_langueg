
#include <cmath>
#include <algorithm>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <unordered_map>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <random>
#include <bitset>
#include <cstdint>
#include <stack>
#include "Lexeme.h"
#include "bor.h"

using namespace std;

void add(string& s, vector<Lexeme>& res, bor& b) {
    if (s.empty()) return;
    res.push_back({b.gagago(s), s});
    if (isdigit(res.back().data[0])) {
        res.back().type = 3;
    }
    s.clear();
}

void addop(string& s, vector<Lexeme>& res, bor& b) {
    if (s.empty()) return;
    string cur;
    for (int i = 0; i < (int)s.size(); ++i) {
        cur.push_back(s[i]);
        if (i < (int)s.size() - 1) {
            cur.push_back(s[i + 1]);
        }
        if (b.gagago(cur)) {
            res.push_back({b.gagago(cur), cur});
            cur.clear();
            ++i;
        } else {
            cur.pop_back();
            res.push_back({b.gagago(cur), cur});
            cur.clear();
        }
    }
    s.clear();
}

void addcom(string& s, vector<Lexeme>& res, bor& b) {
    if (s.empty()) return;
    res.push_back({4, s});
    s.clear();
}

void addstr(string& s, vector<Lexeme>& res, bor& b) {
    if (s.empty()) return;
    res.push_back({5, s});
    s.clear();
}

void adddbl(string& s, vector<Lexeme>& res, bor& b) {
    if (s.empty()) return;
    res.push_back({6, s});
    s.clear();
}

vector<Lexeme> lepsikon(string& s, bor& b) {
    vector<Lexeme> res;
    string cur;
    s.push_back('\n');
    int cond = 0;
    bool is_comment = false, is_string = false;
    int cnt = 1;
    bool is_sharp = false, is_long_comment = false;
    bool is_star = false, is_long_end = false;
    bool double_wait = false;
    for (auto& c : s) {
        if (is_sharp && c == '*') {
            is_long_comment = true;
            is_comment = false;
        }
        if (is_star && c == '#') {
            if (!is_long_comment) {
                cur.pop_back();
                cerr << "[ERROR] ending of the long comment without beginning\n";
                return {};
            }
            is_long_end = true;
        }
        if (c == '#') {
            is_sharp = true;
        } else {
            is_sharp = false;
        }
        if (c == '*') {
            is_star = true;
        } else {
            is_star = false;
        }
        string f;
        f.push_back(c);
        if (double_wait) {
            if (isdigit(c)) {
                cur.push_back(c);
                continue;
            } else {
                adddbl(cur, res, b);
                double_wait = false;
                cond = 0;
            }
        }
        if (is_long_end) {
            addcom(cur, res, b);
            is_long_comment = false;
            is_long_end = false;
        } else if (is_long_comment) {
            cur.push_back(c);
        } else if (is_string) {
            if (c != '"') {
                cur.push_back(c);
            } else {
                addstr(cur, res, b);
                cur.push_back('"');
                add(cur, res, b);
                is_string = false;
            }
        } else if (is_comment) {
            if (c == '\n') {
                ++cnt;
                addcom(cur, res, b);
                is_comment = false;
            } else {
                cur.push_back(c);
            }
        } else if (c == '#') {
            if (cond == 3) {
                addop(cur, res, b);
            } else {
                add(cur, res, b);
            }
            cond = 0;
            is_comment = true;
        } else if (c == '"') {
            if (cond == 3) {
                addop(cur, res, b);
            } else {
                add(cur, res, b);
            }
            cur.push_back('"');
            add(cur, res, b);
            is_string = true;
        } else if (c == ' ' || c == '\n') {
            if (c == '\n') ++cnt;
            if (cond == 3) {
                addop(cur, res, b);
            } else {
                add(cur, res, b);
            }
            cond = 0;
        } else if (b.gagago(f) == 2) {
            if (c == '.' && cond == 1) {
                cur.push_back(c);
                double_wait = true;
                continue;
            }
            if (cond != 3) {
                add(cur, res, b);
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
                cerr << "[ERROR] digit at the beginning of the identifier in the " << cnt << " line\n";
                return {};
            }
            cur.push_back(c);
        } else if (cond == 2) {
            cur.push_back(c);
        } else {
            addop(cur, res, b);
            cur.push_back(c);
            cond = isdigit(c) ? 1 : 2;
        }
    }
    return res;
}

vector<Lexeme> lexrr() {
    bor b;
    ifstream fin("../operator");
    string t;
    while (getline(fin, t)) {
        b.add(t, 2);
    }
    ifstream ff("../key_words");
    while (getline(ff, t)) {
        b.add(t, 1);
    }
    ifstream inp("../input");
    string s;
    while (getline(inp, t)) {
        s += t;
        s += '\n';
    }
    vector<Lexeme> res = lepsikon(s, b);
    vector<Lexeme> ans;
    for (auto& el : res) {
        if (el.type == 4) continue;
        ans.push_back(el);
    }
    return ans;
}

vector<Lexeme> lex_container;

signed main() {
    lex_container = lexrr();
    vector<string> definition{"identifier", "key_word", "operator", "number", "comment", "literal", "double"};
    ofstream out("/home/ivang/mego_true_langueg/output");
    for (auto& el : lex_container) {
        out << "<" << definition[el.type] << ">" << " " << el.data << "\n";
    }
}

// long comment YES
// number of line NO
// double NO