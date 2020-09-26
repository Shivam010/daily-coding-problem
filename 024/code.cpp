/*
Daily Coding Challenge #024
---------------------------
This problem was asked by Google.

Implement locking in a binary tree. A binary tree node can be locked or unlocked
only if all of its descendants or ancestors are not locked.

Design a binary tree node class with the following methods:

- `is_locked`, which returns whether the node is locked.
- `lock`, which attempts to lock the node. If it cannot be locked, then it
should return false. Otherwise, it should lock it and return true.
- `unlock`, which unlocks the node. If it cannot be unlocked, then it should
return false. Otherwise, it should unlock it and return true.

You may augment the node to add parent pointers or any other property you would
like. You may assume the class is used in a single-threaded program, so there is
no need for actual locks or mutexes. Each method should run in `O(h)`, where `h`
is the height of the tree.

Run Using
---------
g++ 024/code.cpp -o bin/out && ./bin/out < 024/in.txt > 024/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    // val: value of node
    int val;

    // stats for locked nodes
    bool state;      // true for lock
    int leftLocks;   // no. of left sub-tree nodes that are locked
    int rightLocks;  // no. of right sub-tree nodes that are locked

    Node *parent;        // parent node
    Node *left, *right;  // children nodes

    Node(Node *par, int v) {
        parent = par;
        val = v;
        state = false;
        leftLocks = rightLocks = 0;
        left = right = NULL;
    }

    bool is_locked() { return state; }

    bool lock() {
        Node *tmp = this;
        bool already = (state+leftLocks + rightLocks > 0);
        while (tmp->parent && !already) {
            tmp = tmp->parent;
            already = tmp->state;
        }
        if (already) {
            cout << "(already locked due to: " << tmp->val
                 << " is_locked:" << (tmp->state ? "true" : "false")
                 << " leftLocks:" << tmp->leftLocks
                 << " rightLocks:" << tmp->rightLocks << ") ";
            return false;
        }
        // the node or its parent are not locked, means the children are also
        // not locked and the current node is free to be locked
        state = true;  // lock node
        // set child lock for parents
        tmp = this;
        Node *par = tmp->parent;
        while (par) {
            if (par->left == tmp)
                par->leftLocks++;
            else
                par->rightLocks++;
            tmp = par;
            par = par->parent;
        }
        return true;
    }

    bool unlock() {
        if (!state) return false;
        state = false;  // unlock it
        // update parent stats
        Node *tmp = this, *par = tmp->parent;
        while (par) {
            if (par->left == tmp)
                par->leftLocks--;
            else
                par->rightLocks--;
            tmp = par;
            par = par->parent;
        }
        return true;
    }
};

void PrintTree(Node *root, string prefix) {
    if (root->right != NULL) PrintTree(root->right, prefix + "\t");
    cout << prefix << root->val << endl;
    if (root->left != NULL) PrintTree(root->left, prefix + "\t");
}

void ScanTree(int n, Node **list) {
    for (int i = 0; i < n; i++) {
        list[i] = NULL;
    }

    n--;
    while (n--) {
        int x, y;
        cin >> x >> y;  // x is parent of y
        if (list[x] == NULL) list[x] = new Node(NULL, x);
        if (list[y] == NULL) list[y] = new Node(list[x], y);
        list[y]->parent = list[x];
        if (list[x]->left == NULL)
            list[x]->left = list[y];
        else
            list[x]->right = list[y];
    }
}

void solve() {
    int n;  // nodes
    cin >> n;
    Node *root, *list[n];
    ScanTree(n, list);
    // considering 0 as root
    root = list[0];
    PrintTree(root, "");

    int q;  // queries
    cin >> q;

    string op;  // operation
    int on;     // on: node index
    bool res;   // response

    while (q--) {
        cin >> op >> on;
        cout << op << " " << on << " ";
        if (op == "lock")
            res = list[on]->lock();
        else if (op == "unlock")
            res = list[on]->unlock();
        else
            res = list[on]->is_locked();
        if (res)
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }
    return;
}

int main() { solve(); }
