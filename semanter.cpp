#include "TID.h"
#include "lexicon.h"
#include "sem_stack.h"

using namespace std;


void roll() {
    TID tid;
    tid.add_node();
    sem_stack st;
    int dfor = 0;
    bool ifor = false, wl = false, ret = false, fnc = false;
    string func_type, func;
    map<string, int> func_table;
    map<string, vector<string>> req_types;
    pair<string, int> pos = {"none", 0};
    while (lex.tp != "end") {
        if (lex.tp == "{") {
            if (ifor) {
                ifor = false;
                dfor = 0;
            } else if (wl) {
                if (st.st_tp.empty() || !st.chi(st.st_tp.back())) {
                    throw "Non bool expression in while";
                }
                wl = false;
            } else if (fnc) {
                fnc = false;
            } else {
                tid.add_node();
            }
            st.st_tp.clear();
            st.st_op.clear();
        } else if (lex.tp == "}") {
            tid.del_node();
        } else if (lex.tp == "type") {
            string t = lex.data;
            if (nextlex() == "{") {
                func_type = t;
            } else {
                if (func_type == "wait") {
                    req_types[func].push_back(t);
                }
                getlex();
                string name = lex.data;
                bool b = tid.add_type(name, t);
                if (!b) {
                    throw "Multiple definition of temp";
                }
            }
        } else if (lex.tp == ";") {
            if (pos.first != "none") {
                if (pos.second == req_types[pos.first].size()) {
                    throw "Too many arguments in function";
                }
                if (st.st_tp.empty() || !(st.chi(st.st_tp.back()) && st.chi(req_types[pos.first][pos.second]))
                   && st.st_tp.back() != req_types[pos.first][pos.second]) {
                    throw "Wrong type of argument of function";
                }
                ++pos.second;
            }
            if (pos.first != "none" && pos.second != req_types[pos.first].size()) {
                throw "Wrong number of function arguments";
            }
            pos = {"none", 0};
            if (ret) {
                if (st.st_tp.empty() || !(st.chi(st.st_tp.back()) && st.chi(func_type)) && st.st_tp.back() != func_type) {
                    throw "Function returns wrong type";
                }
                ret = false;
            }
            if (ifor) {
                if (dfor == 1) {
                    if (st.st_tp.empty() || !st.chi(st.st_tp.back())) {
                        throw "Non bool expression in for";
                    }
                }
                ++dfor;
            }
            st.st_op.clear();
            st.st_tp.clear();
        } else if (lex.tp == "name") { // name
            if (tid.t->par == nullptr) { // function declaration
                if (func_table[lex.data]) {
                    throw "Redefinition of function";
                }
                fnc = true;
                func = lex.data;
                func_type = "wait";
                func_table[lex.data] = 1;
                tid.add_node();
            } else {
                if (nextlex() == "(") {
                    pos = {lex.data, 0};
                    if (func_table.find(lex.data) == func_table.end()) {
                        throw "Call of non-existent function";
                    }
                } else {
                    string t = tid.get_type(lex.data);
                    if (t == "NONE") {
                        throw "Call of non-existent id";
                    }
                    st.add_tp(t);
                }
            }
        } else if (lex.tp == "number") {
            string ss = "int";
            st.add_tp(ss);
        } else if (lex.tp == "double") {
            string ss = "double";
            st.add_tp(ss);
        } else if (lex.tp == "literal") {
            string ss = "string";
            st.add_tp(ss);
        } else if (lex.type == 2) { // operator
            if (lex.tp == ",") {
                if (pos.first != "none") {
                    if (pos.second == req_types[pos.first].size()) {
                        throw "Too many arguments in function";
                    }
                    if (st.st_tp.empty() || !(st.chi(st.st_tp.back()) && st.chi(req_types[pos.first][pos.second]))
                    && st.st_tp.back() != req_types[pos.first][pos.second]) {
                        throw "Wrong type of argument of function";
                    }
                    ++pos.second;
                }
                st.st_tp.clear();
                st.st_op.clear();
            } else {
                st.add_op(lex.tp);
            }
        } else if (lex.tp == "for") {
            tid.add_node();
            ifor = true;
            dfor = 0;
        } else if (lex.tp == "while" || lex.tp == "if") {
            tid.add_node();
            wl = true;
        } else if (lex.tp == "return") {
            ret = true;
        } else if (lex.tp == "main") {
            func_type = "int";
            tid.add_node();
            if (func_table["main"]) {
                throw "Redefinition of main";
            }
            func_table["main"] = 1;
        }
        getlex();
    }
}