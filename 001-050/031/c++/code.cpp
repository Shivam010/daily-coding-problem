// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #031, run using
// g++ 031/code.cpp -o bin/out && ./bin/out < 031/in.txt > 031/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>

void solve() {
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    vi mat[n + 1];
    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            for (int j = 0; j <= m; j++) mat[i].push_back(j);
            continue;
        }
        for (int j = 0; j <= m; j++) mat[i].push_back(0);
        mat[i][0] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int val = mat[i][j - 1] + 1;
            if (val > mat[i - 1][j] + 1) val = mat[i - 1][j] + 1;
            int sub = (a[i - 1] != b[j - 1]);
            if (val > mat[i - 1][j - 1] + sub) val = mat[i - 1][j - 1] + sub;
            mat[i][j] = val;
        }
    }
    cout << endl;
    cout << "==> " << mat[n][m] << endl;
    cout << "    ";
    for (int j = 0; j < m; j++) cout << b[j] << " ";
    cout << endl;
    for (int i = 0; i <= n; i++) {
        if (i != 0)
            cout << a[i - 1] << " ";
        else
            cout << "  ";
        for (int j = 0; j <= m; j++) cout << mat[i][j] << " ";
        cout << endl;
    }
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
