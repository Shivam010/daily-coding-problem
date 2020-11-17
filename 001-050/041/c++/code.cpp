// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #041, run using
// g++ 041/code.cpp -o bin/out && ./bin/out < 041/in.txt > 041/out.txt
#include <bits/stdc++.h>
using namespace std;

bool backtrack(int n, int noUsed, pair<string, string> *list, bool *used,
               string *it) {
    if (noUsed == n) return true;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        if (it[noUsed] == list[i].first) {
            used[i] = true;
            it[++noUsed] = list[i].second;
            if (backtrack(n, noUsed, list, used, it)) return true;
            noUsed--;
            used[i] = false;
        }
    }

    return false;
}

void solve() {
    int n, sz = 0;
    cin >> n;
    pair<string, string> list[n];
    bool used[n];
    for (int i = 0; i < n; i++) {
        cin >> list[i].first >> list[i].second;
        used[i] = false;
    }
    sort(list, list + n);

    string it[n + 1];
    cin >> it[0];
    if (backtrack(n, 0, list, used, it))
        for (int i = 0; i <= n; i++) cout << it[i] << " ";
    else
        cout << -1;
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    fflush(stdin);
    cin.ignore();
    while (t--) {
        solve();
    }
}
