// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #017, run using
// g++ 017/code.cpp -o bin/out && ./bin/out < 017/in.txt > 017/out.txt
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    string name;
    vector<Node *> next;

    Node(string a = "") {
        val = a.size();
        name = a;
        next.clear();
    }
    ~Node() { next.clear(); }

    void print(int level = 0) {
        for (int i = 0; i < level; i++) cout << "\t";
        int n = next.size();
        cout << val << "(" << name << ")" << n << endl;
        for (int i = 0; i < n; i++) next[i]->print(level + 1);
        return;
    }

    int answer() {
        int n = next.size();
        int sl = (n != 0 && name != "");
        int ans = val + sl;
        for (int i = 0; i < n; i++) {
            int tmp = val + sl + next[i]->answer();
            if (ans < tmp) ans = tmp;
        }
        return ans;
    }
};

Node *Create(string str) {
    int n = str.size();
    Node *tree = new Node();
    vector<Node *> par;
    par.push_back(tree);

    string cur = "";
    int i = 0;

    while (i < n) {
        int level = 0;
        while (i + 1 < n && (str[i] == '\\' && str[i + 1] == 't')) {
            i += 2;
            level++;
        }
        int tmp = par.size();
        while (tmp > level + 1) {
            tmp--;
            par.pop_back();
        }

        bool file = false;
        cur = "";
        while (i < n && ((str[i] <= 'z' && str[i] >= 'a') ||
                         (str[i] <= 'Z' && str[i] >= 'A') ||
                         (str[i] <= '9' && str[i] >= '0') || (str[i] == '.'))) {
            if (str[i] == '.') {
                file = true;
            }
            cur.push_back(str[i]);
            i++;
        }
        Node *ch = new Node(cur);
        par[level]->next.push_back(ch);
        // par[0]->print();
        if (!file) par.push_back(ch);
        i += 2;  // \n
    }

    return tree;
}

void solve() {
    string str;
    cin >> str;
    Node *tree = Create(str);
    // tree->print();
    cout << tree->answer() << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
