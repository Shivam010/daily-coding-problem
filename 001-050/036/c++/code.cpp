// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #036, run using
// g++ 036/code.cpp -o bin/out && ./bin/out < 036/in.txt > 036/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    int val;
    Node *left, *right;
    Node(int v) {
        val = v;
        left = right = NULL;
    }
};

int bstSecondLargest(Node *root) {
    if (root == NULL) return -1;
    int rVal = bstSecondLargest(root->right);
    if (rVal != -1) return rVal;
    if (root->right) return root->val;
    Node *left = root->left;
    if (left == NULL) return -1;
    int mx = root->val, sec;
    sec = left->val;
    while (left->right) {
        left = left->right;
        sec = left->val;
    }
    return sec;
}

void solve() {
    int n, val, l, r;
    cin >> n;
    Node *nodes[n];
    for (int i = 0; i < n; i++) nodes[i] = new Node(-1);

    for (int i = 0; i < n; i++) {
        cin >> val >> l >> r;
        nodes[i]->val = val;
        if (l == -1)
            nodes[i]->left = NULL;
        else
            nodes[i]->left = nodes[l];
        if (r == -1)
            nodes[i]->right = NULL;
        else
            nodes[i]->right = nodes[r];
    }
    cout << bstSecondLargest(nodes[0]) << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
