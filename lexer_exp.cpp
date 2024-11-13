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
#include "main.cpp"
#include "Lexer.h"
#include "lexer_exp.h"

void exp0() { // Выражение_запятая

}

void exp1() { // Выражение_присваивания

}


void exp2() { // Выражение_логик_или
    exp4();
    while (lex.get_type() == "||") {
        getlex();
        exp4();
    }
}

void exp3() { // Выражение_логик_и
    exp4();
    while (lex.get_type() == "&&") {
        getlex();
        exp4();
    }
}

void exp4() { // Выражение_бит_или
    exp5();
    while (lex.get_type() == "|") {
        getlex();
        exp5();
    }
}

void exp5() { // Выражение_бит_ксор
    exp6();
    while (lex.get_type() == "^") {
        getlex();
        exp6();
    }
}

void exp6() { // Выражение_бит_и
    exp7();
    while (lex.get_type() == "&") {
        getlex();
        exp7();
    }
}

void exp7() { // Выражение_сравнение
    exp8();
    auto norm {[&]() {return lex.get_type() == ">" || lex.get_type() == "<" ||
    lex.get_type() == ">=" || lex.get_type() == "<=" || lex.get_type() == "!=" || lex.get_type() == "==";}};
    while (norm()) {
        getlex();
        exp8();
    }
}

void exp8() { // Выражение_бит_сдвига
    exp9();
    while (lex.get_type() == "<<" || lex.get_type() == ">>") {
        getlex();
        exp9();
    }
}

void exp9() { // Выражение_простой_арифметики
    exp10();
    while (lex.get_type() == "+" || lex.get_type() == "-") {
        getlex();
        exp10();
    }
}

void exp10() { // Выражение_сложной_арифметики
    exp11();
    while (lex.get_type() == "*" || lex.get_type() == "/" || lex.get_type() == "%") {
        getlex();
        exp11();
    }
}

void exp11() { // Выражение_логического_НЕ
    while (lex.get_type() == "!" || lex.get_type() == "~") {
        getlex();
    }
    exp12();
}

void exp12() { // Выражение_унарного_арифм
    while (lex.get_type() == "$" || lex.get_type() == "@") {
        getlex();
    }
    exp13();
}


void exp13() { // Выражение_инкрементов
    while (lex.get_type() == "++" || lex.get_type() == "--") {
        getlex();
    }
    exp14();
}

void exp14() { // Выражение_индексов
    exp15();
    while (lex.get_type() == "[") {
        getlex();
        exp15();
        if (lex.get_type() != "]") {
            throw "Didn't find ] in exp14";
        }
        getlex();
    }
}


void exp15() { // Выражение_последнее
    if (lex.get_type() == "name") {
        if (nextlex().get_type() == "(") {
            Call_func();
        } else {
            Lexeme();
        }
    } else if (lex.get_type() == "(") {
        Exp_main();
        if (lex.get_type() != ")") {
            throw "Didn't find ) in exp15";
        }
        getlex();
    } else {
        throw "Didn't find ( or name in exp15";
    }
}
