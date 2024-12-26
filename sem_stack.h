#ifndef MEGO_TRUE_LANGUEG_SEM_STACK_H
#define MEGO_TRUE_LANGUEG_SEM_STACK_H

#include "bits/stdc++.h"

using namespace std;

class sem_stack{
public:
    vector<string> st_tp, st_op;

    bool chi(string& s);

    string make_bin(string &t1, string &t2, string &op);

    bool check_un(string& op, string& tp);

    void add_tp(string& tp);

    void add_op(string& op);
};

#endif //MEGO_TRUE_LANGUEG_SEM_STACK_H
