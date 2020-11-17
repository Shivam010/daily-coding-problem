// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #025, run using
// g++ 025/code.cpp -o bin/out && ./bin/out < 025/in.txt > 025/out.txt
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>

bool validate(string &a, string &pat, int &n, int &pn, int i, int j, vi &ans) {
    int in = i * pn + j;
    if (ans[in]) return ans[in] == 1;
    if (i >= n && j >= pn) {
        ans[in] = 1;
        return true;
    }
    if (j + 1 < pn && pat[j + 1] == '*') {
        ans[in] = validate(a, pat, n, pn, i, j + 2, ans);
        if (ans[in] == 1) return true;
        if (i < n && (a[i] == pat[j] || pat[j] == '.')) {
            ans[in] = validate(a, pat, n, pn, i + 1, j, ans);
            if (!ans[in]) ans[in] = -1;
            return ans[in] == 1;
        }
        return false;
    }
    if (i < n && (a[i] == pat[j] || pat[j] == '.')) {
        ans[in] = validate(a, pat, n, pn, i + 1, j + 1, ans);
        if (!ans[in]) ans[in] = -1;
        return ans[in] == 1;
    }
    return false;
}

void solve() {
    string a, pat;
    cin >> a >> pat;
    if (a == "-") a = "";
    int n = a.size(), pn = pat.size();
    vi ans((n + 1) * (pn + 1), 0);  // ans -> 1 true -1 false 0 nothing
    bool res = validate(a, pat, n, pn, 0, 0, ans);
    if (a == "") a = "-";
    if (res)
        cout << a << " ::  valid for  :: " << pat << endl;
    else
        cout << a << " :: invalid for :: " << pat << endl;

    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
