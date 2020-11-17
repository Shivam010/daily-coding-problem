// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #026, run using
// g++ 001-050/026/c++/code.cpp -o bin/out
// ./bin/out < 001-050/026/c++/in.txt > 001-050/026/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    int val;
    Node *next;
    Node(int v) {
        val = v;
        next = NULL;
    }
};

Node *Scan() {
    Node *root = NULL, *cur = NULL;
    string list = "";
    cin.tie(0);
    cin.clear();
    fflush(stdin);
    getline(cin, list);
    int n = list.size(), v = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] == ' ') {
            if (root == NULL)
                root = cur = new Node(v);
            else {
                cur->next = new Node(v);
                cur = cur->next;
            }
            v = 0;
            continue;
        }
        v = v * 10 + list[i] - '0';
    }
    if (n) cur->next = new Node(v);
    return root;
}

void Print(Node *root) {
    Node *v = root;
    while (v) {
        cout << v->val;
        v = v->next;
        if (v) cout << "->";
    }
    cout << endl;
}

void solve() {
    Node *root = Scan();
    Print(root);
    int ql;
    cin >> ql;
    while (ql--) {
        int k, i = 1;
        cin >> k;
        Node *cur = root, *lastK = root, *pre = NULL;
        while (cur->next) {
            if (i >= k) {
                pre = lastK;
                lastK = lastK->next;
            }
            cur = cur->next;
            i++;
        }
        cout << "Last " << k << " th item:: " << lastK->val << endl;
        if (pre == NULL)
            root = root->next;
        else
            pre->next = lastK->next;
        cout << "   After Removing:: ";
        Print(root);
    }
    return;
}

void flush() {
    cin.clear();
    cin.ignore();
    fflush(stdin);
}

int main() {
    int t = 5;
    cin >> t;
    flush();
    while (t--) {
        solve();
        flush();
        cout << "Done" << endl;
    }
}
