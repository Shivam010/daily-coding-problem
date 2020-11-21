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

    void Print() {
        Node* cur = this;
        cout << "List: ";
        while (cur != NULL) {
            cout << cur << " -> ";
            cur = cur->next;
        }
        cout << endl;
    }

    Node* Reverse() {
        Node* cur = this;
        Node *x = NULL, *y = NULL;
        while (cur != NULL) {
            x = cur->next;
            cur->next = y;
            y = cur;
            cur = x;
        }
        return y;
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

    // Reversing both list
    first = first->Reverse();
    second = second->Reverse();

    // cout << "F "<<endl;
    // first->Print();
    // first = first->Reverse();
    // cout << "Reverse F "<<endl;
    // first->Print();

    // cout << "S "<<endl;
    // second->Print();
    // second = second->Reverse();
    // cout << "Reverse S "<<endl;
    // second->Print();

    Node* joint = NULL;
    // And now, check for intersections
    while (first && second) {
        if (first->val == second->val)  // if (first == second)
            // they intersect at
            joint = first;
        first = first->next;
        second = second->next;
    }
    if (joint)
        cout << "Both list interects at: " << joint->val << endl;
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
