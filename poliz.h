//
// Created by ivang on 26.12.24.
//

#ifndef MEGO_TRUE_LANGUEG_POLIZ_H
#define MEGO_TRUE_LANGUEG_POLIZ_H

#include "bits/stdc++.h"
using namespace std;

class poliz {
public:
    vector<string> st, plz;

    void add_plz(string& t);

    int priority(string& op);

    void add_op(string& op);
};


#endif //MEGO_TRUE_LANGUEG_POLIZ_H
