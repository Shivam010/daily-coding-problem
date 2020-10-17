/*
Other Coding Challenge #002
---------------------------
This problem was asked by Turvo.

You are given a tree consisting of `N` vertices, rooted at vertex `1`. Each
vertex consists of a lowercase English alphabet as a node value.

If the ancestor node has the same node value as that of any vertex then that
ancestor node is considered as its valid parent vertex.

Your task is to detach all the nodes from the tree and attach them to any of the
valid parent vertices (in the initial tree) and print the number of connected
components obtained.

For example, the following tree:
```
    1(a)
    /
  2(a)
   \
   3(b)
    \
    4(a)
```
will have 2 connected components:
```
    1(a)
    /   \      and    3(b)
  2(a)  4(a)
```

Run Using
---------
g++ other/002/code.cpp -o bin/out && ./bin/out < other/002/in.txt > \
other/002/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
    int in, val;
    int count[26];
    vector<Node *> next;

    Node(int v, int x) {
        in = x;
        val = v;

        for (int i = 0; i < 26; i++) {
            count[i] = 0;
        }
        count[v] = 1;
    }
};

void iterate(Node *root, vector<int> &answer) {
    // null entry
    if (root == NULL) return;

    int ans = 1, val = root->val;
    int n = root->next.size();

    for (int i = 0; i < n; i++) {
        Node *ne = root->next[i];
        iterate(ne, answer);

        // count characters
        for (int j = 0; j < 26; j++) {
            root->count[j] = root->count[j] + ne->count[j];
            if (ne->count[j] > 0) ans++;
        }

        // undo duplicate count
        root->count[val] -= ne->count[val];
        if (ne->count[val] > 0) ans--;
    }
    // answer
    answer[root->in] = ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        char ch;
        vector<Node *> tree;

        for (int i = 0; i < n; i++) {
            cin >> ch;
            tree.push_back(new Node(ch - 'a', i));
        }

        int u, v;
        for (int i = 0; i < n - 1; i++) {
            cin >> u >> v;
            tree[u - 1]->next.push_back(tree[v - 1]);
        }

        vector<int> answer(n, 0);
        iterate(tree[0], answer);

        cout << answer[0] << endl;
    }
}
