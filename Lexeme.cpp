#include "bits/stdc++.h"
#include "Lexeme.h"

#include <utility>

using namespace std;

Lexeme::Lexeme(int type, string data) : type(type), data(std::move(data)) {}

Lexeme::Lexeme(const Lexeme& other) {
    type = other.type;
    data = other.data;
}
