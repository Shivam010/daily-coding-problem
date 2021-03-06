// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #011, run using
// g++ 001-050/011/c++/code.cpp -o bin/out
// ./bin/out < 001-050/011/c++/in.txt > 001-050/011/c++/out.txt
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int index; // note: using only last index instead of complete list
    Node* next[26];

    Node() {
        index = -1;
        for (int i = 0; i < 26; i++) {
            next[i] = NULL;
        }
    }
    ~Node() {
        for (int i = 0; i < 26; i++) {
            delete next[i];
        }
        delete this;
    }
    Node* Add(char c) {
        if (!next[c - 'a']) next[c - 'a'] = new Node();
        return next[c - 'a'];
    }
    void Mark(int in) { index = in; }
};

void Traverse(Node* trie, vector<int>& ans) {
    if (trie == NULL) return;
    if (trie->index != -1) {
        ans.push_back(trie->index);
    }
    for (int i = 0; i < 26; i++) {
        Node* next = trie->next[i];
        if (next) Traverse(next, ans);
    }
}

void flush() {
    cin.clear();
    fflush(stdin);
}

void solve() {
    flush();

    int allN, queries;
    cin >> allN;
    Node* trie = new Node();

    vector<string> all(allN, "");

    for (int i = 0; i < allN; i++) {
        cin >> all[i];
        int n = all[i].size();
        Node* cur = trie;
        for (int j = 0; j < n; j++) cur = cur->Add(all[i][j]);
        cur->Mark(i);
    }
    flush();

    // queries
    cin >> queries;
    while (queries--) {
        string s;
        cin >> s;
        flush();
        if (trie == NULL) {
            cout << endl;
            continue;
        }

        int n = s.size();

        Node* cur = trie;
        bool notFound = false;
        for (int i = 0; i < n; i++) {
            if (cur->next[s[i] - 'a'])
                cur = cur->next[s[i] - 'a'];
            else {
                notFound = true;
                break;
            }
        }

        if (!notFound) {  // found
            vector<int> ans;
            Traverse(cur, ans);
            int n = ans.size();
            for (int i = 0; i < n; i++) cout << all[ans[i]] << " ";
        }
        cout << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
