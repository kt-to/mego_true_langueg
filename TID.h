#ifndef MEGO_TRUE_LANGUEG_TID_H
#define MEGO_TRUE_LANGUEG_TID_H

#include "bits/stdc++.h"

using namespace std;

class TID{

public:

    struct node{
        node* par;
        map<string, string> dict;

        node() : par(nullptr) {}
    };

    node* t = nullptr;

    bool add_type(string& name, string& type);

    void add_node();

    void del_node();

    string get_type(string& name);
};

#endif //MEGO_TRUE_LANGUEG_TID_H
