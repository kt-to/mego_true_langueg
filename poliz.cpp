#include "poliz.h"

int poliz::priority(string &op) {
    if (op == ";") return -1;
    if (op == "+=" || op == "-=" || op == "/=" || op == "*=" ||
    op == "=" || op == "." || op == "," || op == ")") return 0;
    if (op == "||") return 1;
    if (op == "&&") return 2;
    if (op == "|") return 3;
    if (op == "^") return 4;
    if (op == "&") return 5;
    if (op == "==" || op == "<" || op == ">" || op == ">=" || op == "<=" || op == "!=") return 6;
    if (op == ">>" || op == "<<") return 7;
    if (op == "+" || op == "-") return 8;
    if (op == "*" || op == "/" || op == "%") return 9;
    if (op == "!" || op == "~") return 10;
    if (op == "$" || op == "@") return 11;
    if (op == "++" || op == "--") return 12;
    if (op == "]") return 13;
    if (op == "(" || op == "[" ) return 13;
    return -1;
}

void poliz::add_plz(string &t) {
    plz.push_back(t);
}

void poliz::add_op(string &op) {
    if (op == "]") {
        while (st.back() != "[") {
            add_plz(st.back());
            st.pop_back();
        }
        st.pop_back();
    } else if (op == ")") {
        while (st.back() != "(") {
            add_plz(st.back());
            st.pop_back();
        }
        st.pop_back();
    } else {
        while (!st.empty() && priority(st.back()) >= priority(op) && st.back() != "(" && st.back() != "[") {
            add_plz(st.back());
            st.pop_back();
        }
        if (op != "," && op != ";") {
            st.push_back(op);
        } else {
            add_plz(op);
        }
    }
}
