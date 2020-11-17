// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #001, run using
// g++ 001/code.cpp -o bin/out && ./bin/out < 001/in.txt > 001/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define pb push_back
#define Pi pair<int, int>
#define Pl pair<long long, long long>
#define vi vector<int>
#define vl vector<long long>
#define vb vector<bool>
#define vp vector<pair<int, int>>
#define vpl vector<pair<long long, long long>>
#define F first
#define S second
#define min(a, b) ((a < b) ? a : b)
const ll mod = 1000000007;

int solve() {
    ll n, k, v;
    cin >> n >> k;
    map<ll, bool> mp;
    string ans = "false";
    for (ll i = 0; i < n; i++) {
        cin >> v;
        if (mp[v]) {
            ans = "true";
        }
        mp[k - v] = true;
    }
    cout << ans << endl;
    return 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
