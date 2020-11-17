// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #004, run using
// g++ 004/code.cpp -o bin/out && ./bin/out < 004/in.txt > 004/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>

void solve() {
    int n;
    cin >> n;
    vl a;
    ll x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x > 0) a.push_back(x);
    }
    n = a.size();
    for (int i = 0; i < n; i++) {
        x = abs(a[i]);
        if (x <= n && a[x - 1] > 0) {
            a[x - 1] = -a[x - 1];
        }
    }
    ll ans = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            ans = i + 1;
            break;
        }
    }
    if (ans == -1) ans = n + 1;
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}