// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #030, run using
// g++ 001-050/030/c++/code.cpp -o bin/out
// ./bin/out < 001-050/030/c++/in.txt > 001-050/030/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    int n;
    cin >> n;
    vector<ll> wall(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> wall[i];
    }
    ll ans = 0, mxSt = 0, mxEn = 0;
    int st = 0, en = n - 1;
    while (st <= en) {
        if (wall[st] < wall[en]) {
            if (mxSt <= wall[st])
                mxSt = wall[st];
            else
                ans += mxSt - wall[st];
            st++;
        } else {
            if (mxEn <= wall[en])
                mxEn = wall[en];
            else
                ans += mxEn - wall[en];
            en--;
        }
    }
    cout << ans << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
