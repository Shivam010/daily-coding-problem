// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #006, run using
// g++ 001-050/006/c++/code.cpp -o bin/out
// ./bin/out < 001-050/006/c++/in.txt > 001-050/006/c++/out.txt
#include <bits/stdc++.h>
using namespace std;

class Node {
   public:
    int val;
    Node* both;

    Node(int v) { this->val = v; }

    void add(Node* el) {
        Node *it = this, *pre = NULL;
        while (it->both != NULL) {
            Node* next = (Node*)(uintptr_t(it->both) ^ uintptr_t(pre));
            it = next;
        }
        it->both = (Node*)(uintptr_t(pre) ^ uintptr_t(el));
    }

    Node* get(int in) {
        Node *it = this, *pre = NULL;
        int i = 0;
        while (i != in && it != NULL) {
            it = (Node*)(uintptr_t(it->both) ^ uintptr_t(pre));
            i++;
        }
        return it;
    }

    void print() {
        Node *it = this, *pre = NULL;
        while (it != NULL) {
            cout << it->val << " ";
            it = (Node*)(uintptr_t(it->both) ^ uintptr_t(pre));
        }
        cout << endl;
    }
};

Node* XOR(Node* a, Node* b) { return (Node*)((uintptr_t)a ^ (uintptr_t)b); }

int main() {
    int t;
    Node* a = new Node(8);
    a->add(new Node(7));
    a->add(new Node(6));
    a->add(new Node(5));
    a->add(new Node(4));
    a->print();
    Node* v = a->get(2);
    Node* vv = a->get(4);
    Node* x = a->get(5);
    cout << v->val << " " << vv->val << " " << x << endl;
    return 0;
}