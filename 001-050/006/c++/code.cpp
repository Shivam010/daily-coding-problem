// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #006, run using
// g++ 001-050/006/c++/code.cpp -o bin/out
// ./bin/out
#include <bits/stdc++.h>
using namespace std;

class Node {
   public:
    int val;
    Node* both;

    Node(int v) { this->val = v; }

    void add(Node* el) {
        Node *it = this, *pre = NULL, *next;
        while (it->both != NULL) {
            next = (Node*)(uintptr_t(it->both) ^ uintptr_t(pre));
            pre = it;
            it = next;
        }
        it->both = (Node*)(uintptr_t(pre) ^ uintptr_t(el));
    }

    Node* get(int in) {
        Node *it = this, *pre = NULL, *next;
        int i = 0;
        while (i < in && it->both != NULL) {
            next = (Node*)(uintptr_t(it->both) ^ uintptr_t(pre));
            pre = it;
            it = next;
            i++;
        }
        if(i<in) return NULL;
        return it;
    }

    void print() {
        int i = -1;
	Node *cur = get(++i);
	while(cur) {
	    cout<<cur->val<<" ";
	    cur = get(++i);
	}
        cout << endl;
    }
};

Node* XOR(Node* a, Node* b) { return (Node*)((uintptr_t)a ^ (uintptr_t)b); }

int main() {
    int t;
    Node* a = new Node(8);
    a->add(new Node(7));
    Node* im = a->get(0);
    a->add(new Node(6));
    a->add(new Node(5));
    a->add(new Node(4));
    a->print();
    Node* v = a->get(2);
    Node* vv = a->get(4);
    Node* x = a->get(5);
    cout << im->val<< " " << v->val << " " << vv->val << " " << x << endl;
    return 0;

    // Output:
    //  8 7 6 5 4
    //  8 6 4 0x0
}