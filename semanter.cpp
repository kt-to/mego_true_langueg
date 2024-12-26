#include "TID.h"
#include "lexicon.h"
#include "sem_stack.h"

using namespace std;

void roll() {
    TID tid;
    tid.add_node();
    sem_stack st;
    int dfor = 0;
    bool ifor = false, wl = false, ret = false;
    string func_type;
    map<string, int> func_table;
    while (lex.tp != "end") {
        if (lex.tp == "{") {
            if (ifor) {
                ifor = false;
                dfor = 0;
                tid.add_node();
            } else if (wl) {
                if (st.st_tp.empty() || !st.chi(st.st_tp.back())) {
                    throw "Non bool expression in while";
                }
                wl = false;
                tid.add_node();
            } else {
                tid.add_node();
            }
            st.st_tp.clear();
            st.st_op.clear();
        } else if (lex.tp == "}") {
            tid.del_node();
            if (tid.tk) {
                tid.del_node();
            }
        } else if (lex.tp == "type") {
            string t = lex.data;
            if (nextlex() == "{") {
                func_type = t;
            } else {
                getlex();
                string name = lex.data;
                bool b = tid.add_type(name, t);
                if (!b) {
                    throw "Multiple definition of temp";
                }
            }
        } else if (lex.tp == ";") {
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
                func_table[lex.data] = 1;
                tid.add_node();
                tid.tk = true;
            } else {
                string t = tid.get_type(lex.data);
                if (t == "NONE") {
                    throw "Call of non-existent id";
                }
                st.add_tp(t);
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
                st.add_op(lex.tp);
        } else if (lex.tp == "for") {
            tid.add_node();
            tid.tk = true;
            ifor = true;
            dfor = 0;
        } else if (lex.tp == "while" || lex.tp == "if") {
            tid.add_node();
            tid.tk = true;
            wl = true;
        } else if (lex.tp == "return") {
            ret = true;
        } else if (lex.tp == "main") {
            func_type = "int";
            tid.add_node();
            tid.tk = true;
            if (func_table["main"]) {
                throw "Redefinition of main";
            }
            func_table["main"] = 1;
        }
        getlex();
    }
}