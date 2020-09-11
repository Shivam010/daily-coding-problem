/*
Daily Coding Challenge #008
---------------------------
A unival tree (which stands for "universal value") is a tree where all nodes
under it have the same value.

Given the root to a binary tree, count the number of unival subtrees.

For example, the following tree has 5 unival subtrees:

   0
  / \
 1   0
    / \
   1   0
  / \
 1   1

Run Using
---------
g++ 008/code.cpp -o bin/out && ./bin/out < 008/in.txt > 008/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>

struct Node {
    int val;
    bool uni;
    int ans;
    Node *left, *right;  // index of left and right, 0 for NULL

    Node(int v) {
        val = v;
        uni = false;
        ans = 0;
        left = right = NULL;
    }
    void AddChild(Node *ch) {
        if (left)
            right = ch;
        else
            left = ch;
    }
    void Print(int in) {
        cout << in << "\t" << val << "\t" << uni << "\t" << left << "\t"
             << right << "\t" << ans << "\t" << endl;
    }
};

int solve(Node *root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        root->uni = true;
        return ++(root->ans);
    }

    if (root->left && root->right) {
        Node *left = root->left, *right = root->right;
        root->ans += solve(root->left) + solve(root->right);
        if (left->uni && right->uni && left->val == right->val &&
            root->val == left->val) {
            root->uni = true;
            root->ans++;
        }
        return root->ans;
    }
    Node *ch = root->left ? root->left : root->right;
    root->ans += solve(ch);
    if (ch->uni && ch->val == root->val) {
        root->uni = true;
        root->ans++;
    }
    return root->ans;
}

/*
Input

Example 1:

 Values   =>  Indexes
   0            1
  / \          / \
 1   0        2   3
    / \   =>     / \
   1   0        4   5
  / \          / \
 1   1        6   7

7
0 2 2 3
1 0
0 2 4 5
1 2 6 7
0 0
1 0
1 0
Answer => 5

Example 2:

 Values   =>  Indexes
   0            1
   |            |
   1            2

2
0 1 1
1 0
Answer => 1

*/
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;  // no. of nodes
        cin >> n;

        vi val(n + 1, 0);
        Node *list[n + 1];
        for (int i = 1; i <= n; i++) list[i] = new Node(0);

        for (int i = 1; i <= n; i++) {
            int val, no;  // val: value of node i; and no: # of childs
            cin >> val >> no;
            list[i]->val = val;
            int ch;
            if (no > 0) {
                cin >> ch;
                list[i]->left = list[ch];
            }
            if (no == 2) {
                cin >> ch;
                list[i]->right = list[ch];
            }
        }

        cout << solve(list[1]) << endl;

        // for (int i = 1; i <= n; i++) {
        //     list[i]->Print(i);
        // }
        // cout << endl;
    }
}
