#ifndef MEGO_TRUE_LANGUEG_LEXEME_H
#define MEGO_TRUE_LANGUEG_LEXEME_H
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
#pragma once

using namespace std;

class Lexeme{
public:
    int type;
    string data;
    string tp;

    Lexeme(int type = 0, string data = {}, string tp = {});

    Lexeme(const Lexeme& other);

    string get_type();
};

#endif //MEGO_TRUE_LANGUEG_LEXEME_H
