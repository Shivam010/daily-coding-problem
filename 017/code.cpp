/*
Daily Coding Challenge #017
---------------------------
This problem was asked by Google.

Suppose we represent our file system by a string in the following manner:

The string `"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"` represents:

    dir
        subdir1
        subdir2
            file.ext

The directory `dir` contains an empty sub-directory `subdir1` and a
sub-directory `subdir2` containing a file `file.ext`.

The string
`"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"`
represents:

    dir
        subdir1
            file1.ext
            subsubdir1
        subdir2
            subsubdir2
                file2.ext

The directory `dir` contains two sub-directories `subdir1` and `subdir2`.
`subdir1` contains a file `file1.ext` and an empty second-level sub-directory
`subsubdir1`. `subdir2` contains a second-level sub-directory `subsubdir2`
containing a file `file2.ext`.

We are interested in finding the longest (number of characters) absolute path to
a file within our file system. For example, in the second example above, the
longest absolute path is `"dir/subdir2/subsubdir2/file2.ext"`, and its length is
32 (not including the double quotes).

Given a string representing the file system in the above format, return the
length of the longest absolute path to a file in the abstracted file system. If
there is no file in the system, return 0.

Note:

The name of a file contains at least a period and an extension.

The name of a directory or sub-directory will not contain a period.

Run Using
---------
g++ 017/code.cpp -o bin/out && ./bin/out < 017/in.txt > 017/out.txt
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    string name;
    vector<Node *> next;

    Node(string a = "") {
        val = a.size();
        name = a;
        next.clear();
    }
    ~Node() { next.clear(); }

    void print(int level = 0) {
        for (int i = 0; i < level; i++) cout << "\t";
        int n = next.size();
        cout << val << "(" << name << ")" << n << endl;
        for (int i = 0; i < n; i++) next[i]->print(level + 1);
        return;
    }

    int answer() {
        int n = next.size();
        int sl = (n != 0 && name != "");
        int ans = val + sl;
        for (int i = 0; i < n; i++) {
            int tmp = val + sl + next[i]->answer();
            if (ans < tmp) ans = tmp;
        }
        return ans;
    }
};

Node *Create(string str) {
    int n = str.size();
    Node *tree = new Node();
    vector<Node *> par;
    par.push_back(tree);

    string cur = "";
    int i = 0;

    while (i < n) {
        int level = 0;
        while (i + 1 < n && (str[i] == '\\' && str[i + 1] == 't')) {
            i += 2;
            level++;
        }
        int tmp = par.size();
        while (tmp > level + 1) {
            tmp--;
            par.pop_back();
        }

        bool file = false;
        cur = "";
        while (i < n && ((str[i] <= 'z' && str[i] >= 'a') ||
                         (str[i] <= 'Z' && str[i] >= 'A') ||
                         (str[i] <= '9' && str[i] >= '0') || (str[i] == '.'))) {
            if (str[i] == '.') {
                file = true;
            }
            cur.push_back(str[i]);
            i++;
        }
        Node *ch = new Node(cur);
        par[level]->next.push_back(ch);
        // par[0]->print();
        if (!file) par.push_back(ch);
        i += 2;  // \n
    }

    return tree;
}

void solve() {
    string str;
    cin >> str;
    Node *tree = Create(str);
    // tree->print();
    cout << tree->answer() << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
