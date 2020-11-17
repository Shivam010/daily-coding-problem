// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #034, run using
// g++ 001-050/034/c++/code.cpp -o bin/out
// ./bin/out < 001-050/034/c++/in.txt > 001-050/034/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>

int answer(string &a, int n, int i, int j, vi &ans) {
    if (i >= j) return 0;
    if (ans[i * n + j] > -1) return ans[i * n + j];
    if (a[i] == a[j]) {
        ans[i * n + j] = answer(a, n, i + 1, j - 1, ans);
        return ans[i * n + j];
    }
    int ans1 = answer(a, n, i + 1, j, ans);
    int ans2 = answer(a, n, i, j - 1, ans);
    ans[i * n + j] = 1 + ((ans1 < ans2) ? ans1 : ans2);
    return ans[i * n + j];
}

void solve() {
    string a;
    cin >> a;
    int n = a.size();
    vi ans(n * (n + 1), -1);
    cout << answer(a, n, 0, n - 1, ans) << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
