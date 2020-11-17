// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #048, run using
// g++ 048/code.cpp -o bin/out && ./bin/out < 048/in.txt > 048/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    char val;
    Node *left, *right;
    Node(char v) {
        val = v;
        left = right = NULL;
    }
    void Preorder(string &str) {
        str.push_back(val);
        if (left) left->Preorder(str);
        if (right) right->Preorder(str);
    }
    void Inorder(string &str) {
        if (left) left->Inorder(str);
        str.push_back(val);
        if (right) right->Inorder(str);
    }
};

void solve() {
    int n;
    cin >> n;
    assert(n > 0);
    string in, pre;
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        pre.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        in.push_back(x);
    }
    stack<Node *> st;
    Node *root, *cur, *last;
    bool right = false;
    for (int j = 0, i = 0; i < n; i++) {
        cur = new Node(pre[i]);
        if (i == 0)
            root = cur;
        else if (right)
            last->right = cur;
        else
            last->left = cur;
        st.push(cur);
        last = cur;
        right = false;
        while (!st.empty() && j < n && st.top()->val == in[j]) {
            last = st.top();
            st.pop();
            j++;
            right = true;
        }
    }
    string ansPre, ansIn;
    root->Preorder(ansPre);
    root->Inorder(ansIn);
    if (ansPre == pre && ansIn == in)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    cout << "Answer" << endl;
    cout << "\t Preorder: " << ansPre << endl;
    cout << "\t Inorder:: " << ansIn << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
