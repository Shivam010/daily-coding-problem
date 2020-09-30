/*
Daily Coding Challenge #026
---------------------------
This problem was asked by Google.

Given a singly linked list and an integer k, remove the kth last element from
the list. k is guaranteed to be smaller than the length of the list.

The list is very long, so making more than one pass is prohibitively expensive.

Do this in constant space and in one pass.

Run Using
---------
g++ 026/code.cpp -o bin/out && ./bin/out < 026/in.txt > 026/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    int val;
    Node *next;
    Node(int v) {
        val = v;
        next = NULL;
    }
};

Node *Scan() {
    Node *root = NULL, *cur = NULL;
    string list = "";
    cin.tie(0);
    cin.clear();
    fflush(stdin);
    getline(cin, list);
    int n = list.size(), v = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] == ' ') {
            if (root == NULL)
                root = cur = new Node(v);
            else {
                cur->next = new Node(v);
                cur = cur->next;
            }
            v = 0;
            continue;
        }
        v = v * 10 + list[i] - '0';
    }
    if (n) cur->next = new Node(v);
    return root;
}

void Print(Node *root) {
    Node *v = root;
    while (v) {
        cout << v->val;
        v = v->next;
        if (v) cout << "->";
    }
    cout << endl;
}

void solve() {
    Node *root = Scan();
    Print(root);
    int ql;
    cin >> ql;
    while (ql--) {
        int k, i = 1;
        cin >> k;
        Node *cur = root, *lastK = root, *pre = NULL;
        while (cur->next) {
            if (i >= k) {
                pre = lastK;
                lastK = lastK->next;
            }
            cur = cur->next;
            i++;
        }
        cout << "Last " << k << " th item:: " << lastK->val << endl;
        if (pre == NULL)
            root = root->next;
        else
            pre->next = lastK->next;
        cout << "   After Removing:: ";
        Print(root);
    }
    return;
}

void flush() {
    cin.clear();
    cin.ignore();
    fflush(stdin);
}

int main() {
    int t = 5;
    cin >> t;
    flush();
    while (t--) {
        solve();
        flush();
        cout << "Done" << endl;
    }
}