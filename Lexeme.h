#ifndef MEGO_TRUE_LANGUEG_LEXEME_H
#define MEGO_TRUE_LANGUEG_LEXEME_H
#include "bits/stdc++.h"
#pragma once

using namespace std;

class Lexeme{
public:
    int type;
    string data;

    Lexeme(int type, string data);

    Lexeme(const Lexeme& other);
};

#endif //MEGO_TRUE_LANGUEG_LEXEME_H
