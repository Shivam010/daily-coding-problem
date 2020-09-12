/*
Daily Coding Challenge #006
---------------------------
This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list. Instead of
each node holding next and prev fields, it holds a field named both, which is an
XOR of the next node and the previous node. Implement an XOR linked list; it has
an add(element) which adds the element to the end, and a get(index) which
returns the node at index.

If using a language that has no pointers (such as Python), you can assume you
have access to get_pointer and dereference_pointer functions that converts
between nodes and memory addresses.

Run Using
---------
g++ 006/code.cpp -o bin/out && ./bin/out < 006/in.txt > 006/out.txt
*/
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