// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #022, run using
// g++ 001-050/022/c++/code.cpp -o bin/out
// ./bin/out < 001-050/022/c++/in.txt > 001-050/022/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vs vector<string>
#define hash(n, i, j) ((i * n + j))

vs answer(vs *dp, vs &dic, string &word, int st, int n, int dicLen) {
    if (dp[st].size() > 0) {
        return dp[st];
    }
    vs res;
    string tmp = "";
    for (int j = st; j < n; j++) {
        bool found = false;
        tmp.push_back(word[j]);
        for (int i = 0; i < dicLen; i++) {
            if (dic[i] == tmp) {
                found = true;
                break;
            }
        }
        if (found) {
            if (j == n - 1) {
                res.push_back(tmp);
                dp[st] = res;
                return res;
            }
            res = answer(dp, dic, word, j + 1, n, dicLen);
            if (res.size() > 0) {
                res.push_back(tmp);
                dp[st] = res;
                return res;
            }
        }
    }
    dp[st] = res;
    return res;
}

void solve() {
    int dicLen;
    cin >> dicLen;
    fflush(stdin);
    vs dic(dicLen, "");
    for (int i = 0; i < dicLen; i++) {
        cin >> dic[i];
    }
    string word;
    cin >> word;
    int n = word.size();
    vs dp[n + 1];
    vs ans = answer(dp, dic, word, 0, n, dicLen);
    n = ans.size();
    if (n == 0) {
        cout << "-\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
