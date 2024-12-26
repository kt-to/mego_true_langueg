#include "sem_stack.h"

bool is_un(string& op) {
    return op == "$" || op == "@" || op == "++" || op == "--" || op == "!";
}

bool chl(string& s) {
    return s != "array" && s != "string";
}

bool sem_stack::chi(string& s) {
    return s == "int" || s == "char" || s == "bool";
}

bool str(string& s) {
    return s == "string" || s == "char";
}

string sem_stack::make_bin(string &t1, string &t2, string &op) {
    if (op == "&" || op == "|" || op == "^" || op == "&&" || op == "||" || op == "%" || op == "<<" || op == ">>") {
        if (chi(t1) && chi(t2)) {
            if (op == "&&" || op == "||") return "bool";
            return "int";
        }
    } else if (op == "+" || op == "-" || op == "*" || op == "/") {
        if (op == "+" && str(t1) && str(t2) && (t1 == "string" || t2 == "string")) {
            return "string";
        }
        if (chl(t1) && chl(t2)) {
            if (t1 == "float" || t2 == "float") return "float";
            return "int";
        }
    } else if (op == ">=" || op == "<=" || op == "==" || op == "!=" || op == ">" || op == "<" ) {
        if (chl(t1) && chl(t2)) {
            return "bool";
        }
        if (t1 == t2) {
            return "bool";
        }
    } else if (op == "=" || op == "+=" || op == "-=" || op == "/=" || op == "*=") {
        if (chl(t1) && chl(t2)) return t1;
        if (t1 == t2) {
            if (op == "=" || op == "+=" && t1 == "string") return t1;
        }
    }
    return "bad";
}

bool sem_stack::check_un(string &op, string &type) {
    return chl(type);
}

void sem_stack::add_tp(string &type) {
    while (!st_op.empty() && is_un(st_op.back())) {
        if (!check_un(st_op.back(), type)) throw "Wrong unary operation";
        st_op.pop_back();
    }
    if (st_tp.empty()) {
        st_tp.push_back(type);
    } else {
        if (st_op.empty()) {
            throw "No operator between temps";
        } else {
            string res = make_bin(st_tp.back(), type, st_op.back());
            st_tp.pop_back();
            st_op.pop_back();
            if (res == "bad") {
                throw "Wrong binary operation";
            }
            st_tp.push_back(res);
        }
    }
}

void sem_stack::add_op(string& op) {
    if (op == "(" || op == ")" || op == "." || op == ",") return;
    st_op.push_back(op);
}

