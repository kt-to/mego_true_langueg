#include "TID.h"


bool TID::add_type(string& name, string& type) {
    if (t->dict.find(name) != t->dict.end()) {
        return false;
    }
    t->dict[name] = type;
    return true;
}

void TID::add_node() {
    node* nw = new node();
    nw->par = t;
    t = nw;
}

void TID::del_node() {
    node* nw = t;
    t = t->par;
    delete nw;
}

string TID::get_type(string& name) {
    node* cur = t;
    while (cur != nullptr) {
        if (cur->dict.find(name) != cur->dict.end()) {
            return cur->dict[name];
        }
        cur = cur->par;
    }
    return "NONE";
}