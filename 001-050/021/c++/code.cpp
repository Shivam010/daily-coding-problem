// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #021, run using
// g++ 021/code.cpp -o bin/out && ./bin/out < 021/in.txt > 021/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define pb push_back
#define pl pair<ll, ll>
#define vl vector<ll>
#define vp vector<pair<ll, ll> >

void solve() {
    int n;
    cin >> n;
    vp list(n, mk(0, 0));
    for (int i = 0; i < n; i++) {
        cin >> list[i].first >> list[i].second;
    }
    sort(list.begin(), list.end());
    vl starts(n, 0), ends(n, 0);
    for (int i = 0; i < n; i++) {
        starts[i] = list[i].first;
        ends[i] = list[i].second;
    }
    int si = 0, ei = 0;
    int cnt = 0, mx = 0;
    while (si < n && ei < n) {
        if (starts[si] <= ends[ei])
            cnt++, si++;
        else
            cnt--, ei++;
        if (mx < cnt) mx = cnt;
    }
    cout << mx << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
