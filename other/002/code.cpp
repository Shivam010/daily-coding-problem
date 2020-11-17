// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge Other#002, run using
// g++ other/002/code.cpp -o bin/out
// ./bin/out < other/002/in.txt > other/002/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    int in, val;
    int count[26];
    vector<Node *> next;

    Node(int v, int x) {
        in = x;
        val = v;

        for (int i = 0; i < 26; i++) {
            count[i] = 0;
        }
        count[v] = 1;
    }
};

void iterate(Node *root, vector<int> &answer) {
    // null entry
    if (root == NULL) return;

    int ans = 1, val = root->val;
    int n = root->next.size();

    for (int i = 0; i < n; i++) {
        Node *ne = root->next[i];
        iterate(ne, answer);

        // count characters
        for (int j = 0; j < 26; j++) {
            root->count[j] = root->count[j] + ne->count[j];
            if (ne->count[j] > 0) ans++;
        }

        // undo duplicate count
        root->count[val] -= ne->count[val];
        if (ne->count[val] > 0) ans--;
    }
    // answer
    answer[root->in] = ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        char ch;
        vector<Node *> tree;

        for (int i = 0; i < n; i++) {
            cin >> ch;
            tree.push_back(new Node(ch - 'a', i));
        }

        int u, v;
        for (int i = 0; i < n - 1; i++) {
            cin >> u >> v;
            tree[u - 1]->next.push_back(tree[v - 1]);
        }

        vector<int> answer(n, 0);
        iterate(tree[0], answer);

        cout << answer[0] << endl;
    }
}
