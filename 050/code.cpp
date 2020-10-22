/*
Daily Coding Challenge #050
---------------------------
This problem was asked by Microsoft.

Suppose an arithmetic expression is given as a binary tree. Each leaf is an
integer and each internal node is one of `'+', '−', '∗', or '/'`.

Given the root to such a tree, write a function to evaluate it.

For example, given the following tree:
```
    *
   / \
  +    +
 / \  / \
3  2  4  5
```
You should return `45`, as it is `(3 + 2) * (4 + 5)`.

Run Using
---------
g++ 050/code.cpp -o bin/out && ./bin/out < 050/in.txt > 050/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    string val;
    Node *left, *right;
    Node(string v) {
        val = v;
        left = right = NULL;
    }
    void Inorder(string &str) {
        if (left) {
            str += " (";
            left->Inorder(str);
            str += ") ";
        }
        str += val;
        if (right) {
            str += " (";
            right->Inorder(str);
            str += ") ";
        }
    }
    int Solve() {
        int leftPart = 0, rightPart = 0;
        if (left) leftPart = left->Solve();
        if (right) rightPart = right->Solve();
        if (!left && !right) {
            int n = val.size(), i = 0;
            while (i < n) leftPart = leftPart * 10 + (val[i++] - '0');
            return leftPart;
        }
        if (val == "+") return leftPart + rightPart;
        if (val == "-") return leftPart - rightPart;
        if (val == "*") return leftPart * rightPart;
        if (val == "/" && rightPart) return leftPart / rightPart;
        return INFINITY;
    }
};

void solution() {
    int n;  // no. of nodes in tree
    cin >> n;
    string values[n];
    Node *nodes[n];
    for (int i = 0; i < n; i++) {
        // values of each node
        cin >> values[i];
        nodes[i] = new Node(values[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        // edges - index `one` is linked with index `two`
        int one, two;
        cin >> one >> two;
        if (nodes[one]->left == NULL)
            nodes[one]->left = nodes[two];
        else if (nodes[one]->right == NULL)
            nodes[one]->right = nodes[two];
        else
            throw "Invalid binary tree provided";
    }
    // considering 0th index as root
    Node *root = nodes[0];
    string exp = "";
    root->Inorder(exp);
    cout << "Expression =>" << exp << endl;
    cout << "Result => " << root->Solve() << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solution();
    }
}
