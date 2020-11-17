// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #029, run using
// g++ 001-050/029/c++/code.cpp -o bin/out
// ./bin/out < 001-050/029/c++/in.txt > 001-050/029/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

string encode(string in) {
    string out = "", tmp;
    int n = in.size(), cnt;
    char c;
    for (int i = 0; i < n;) {
        c = in[i++];
        cnt = 1;
        while (c == in[i]) cnt++, i++;
        tmp = c;
        while (cnt) {
            c = '0' + (cnt % 10);
            tmp = c + tmp;
            cnt /= 10;
        }
        out += tmp;
    }
    return out;
}

string decode(string in) {
    string out = "", tmp;
    int n = in.size(), cnt;
    for (int i = 0; i < n; i++) {
        cnt = 0;
        while (in[i] <= '9' && in[i] >= '0') cnt = cnt * 10 + in[i] - '0', i++;
        while (cnt--) out.push_back(in[i]);
    }
    return out;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string op, str;
        cin >> op >> str;
        if (op == "enc")
            cout << str << " ::enc:: " << encode(str) << endl;
        else
            cout << str << " ::dec:: " << decode(str) << endl;
    }
}
