#ifndef MEGO_TRUE_LANGUEG_LEXICON_H
#define MEGO_TRUE_LANGUEG_LEXICON_H
#pragma once
#include "iostream"
#include "string"
#include "vector"
#include "Lexeme.h"
#include "bor.h"

void add(string& s, vector<Lexeme>& res, bor& b);

void addop(string& s, vector<Lexeme>& res, bor& b);

void addcom(string& s, vector<Lexeme>& res, bor& b);

void addstr(string& s, vector<Lexeme>& res, bor& b);

void adddbl(string& s, vector<Lexeme>& res, bor& b);

vector<Lexeme> lepsikon(string& s, bor& b);

vector<Lexeme> lexrr();

inline int cur = 0;
inline vector<Lexeme> lex_container;
inline Lexeme lex;

void getlex();

Lexeme nextlex();

#endif //MEGO_TRUE_LANGUEG_LEXICON_H
