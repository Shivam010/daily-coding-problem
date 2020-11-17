// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #020, run using
// g++ 001-050/020/c++/code.cpp -o bin/out
// ./bin/out < 001-050/020/c++/in.txt > 001-050/020/c++/out.txt
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;

    Node(int v) {
        val = v;
        next = NULL;
    }
    Node(string str) {
        int n = str.size();
        int c = 0, i = 0;
        while (i < n && str[i] >= '0' && str[i] <= '9') {
            c = c * 10 + (str[i] - '0');
            i++;
        }
        val = c;
        next = NULL;
        c = 0;

        Node* cur = this;

        i += 2;  // remove "->"
        while (i < n) {
            while (str[i] >= '0' && str[i] <= '9') {
                c = c * 10 + (str[i] - '0');
                i++;
            }
            cur->next = new Node(c);
            cur = cur->next;
            c = 0;
            i += 2;  // remove "->"
        }
    }
    ~Node() { delete next; }

    int length() {
        int len = 0;
        Node* cur = this;
        while (cur != NULL) {
            len++;
            cur = cur->next;
        }
        return len;
    }
};

void flush() {
    cin.clear();
    fflush(stdin);
}

void solve() {
    Node *first = NULL, *second = NULL;
    string F, S;
    cin >> F >> S;
    flush();
    first = new Node(F);
    second = new Node(S);

    int fn = first->length(), sn = second->length();
    if (sn > fn) {
        swap(fn, sn);
        swap(first, second);
    }

    // till both are of equal lengths;
    while (fn > sn) first = first->next, fn--;
    while (sn > fn) second = second->next, sn--;

    // And now, if both list's pointers intersect, then the upcoming while
    // condition, `(first && second && first->val != second->val)` can be
    // changed to `(first && second && first != second)`
    while (first && second && first->val != second->val) {
        first = first->next;
        second = second->next;
    }
    if (first && second)
        cout << "Interects at value: " << first->val << ", pointor" << first
             << endl;
    else
        cout << "Both list never intersects" << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
