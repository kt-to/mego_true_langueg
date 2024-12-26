#include "lexer_exp.h"

void exp0() { // Выражение_запятая
    exp1();
    while (lex.get_type() == ",") {
        getlex();
        exp1();
    }
}

void exp1() { // Выражение_присваивания
    auto norm {[&]() {return lex.get_type() == "=" || lex.get_type() == "+=" ||
    lex.get_type() == "-=" || lex.get_type() == "*=" || lex.get_type() == "/=" || lex.get_type() == "%=";}};
    exp2();
    while (norm()) {
        getlex();
        exp2();
    }
}


void exp2() { // Выражение_логик_или
    exp3();
    while (lex.get_type() == "||") {
        getlex();
        exp3();
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
        if (nextlex() == "(") {
            Call_func();
        } else {
            Literal();
        }
    } else if (lex.get_type() == "(") {
        getlex();
        exp0();
        if (lex.get_type() != ")") {
            throw "Didn't find ) in exp15";
        }
        getlex();
    } else {
        Literal();
    }
}
