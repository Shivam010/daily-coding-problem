// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #002, run using
// g++ 001-050/002/c++/code.cpp -o bin/out
// ./bin/out < 001-050/002/c++/in.txt > 001-050/002/c++/out.txt
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

void solve() {
    ll n;
    cin >> n;
    assert(n > 1);
    vl a(n, 0), left(n, 1), right(n, 1);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    left[0] = a[0];
    for (ll i = 1; i < n; i++) {
        left[i] = 1LL * left[i - 1] * a[i];
    }
    right[n - 1] = a[n - 1];
    for (ll i = n - 2; i > -1; i--) {
        right[i] = 1LL * right[i + 1] * a[i];
    }
    cout << right[1] << " ";
    for (ll i = 1; i < n - 1; i++) {
        cout << 1LL * left[i - 1] * right[i + 1] << " ";
    }
    cout << left[n - 2] << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
