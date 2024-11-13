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

#include <utility>

using namespace std;

Lexeme::Lexeme(int type, string data) : type(type), data(std::move(data)) {}

Lexeme::Lexeme(const Lexeme& other) {
    type = other.type;
    data = other.data;
}
