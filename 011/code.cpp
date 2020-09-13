/*
Daily Coding Challenge #011
---------------------------
This problem was asked by Twitter.

Implement an autocomplete system. That is, given a query string s and a set of
all possible query strings, return all strings in the set that have s as a
prefix.

For example, given the query string `de` and the set of strings `[dog, deer,
deal]`, return `[deer, deal]`.

Hint: Try preprocessing the dictionary into a more efficient data structure to
speed up queries.

Run Using
---------
g++ 011/code.cpp -o bin/out && ./bin/out < 011/in.txt > 011/out.txt
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> indices;
    Node* next[26];

    Node() {
        indices = vector<int>();
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
    void Mark(int in) { indices.push_back(in); }
};

void Traverse(Node* trie, vector<int>& ans) {
    if (trie == NULL) return;
    int n = trie->indices.size();
    for (int j = 0; j < n; j++) ans.push_back(trie->indices[j]);
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
