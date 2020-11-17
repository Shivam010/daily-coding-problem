// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #009, run using
// g++ 001-050/009/c++/code.cpp -o bin/out
// ./bin/out < 001-050/009/c++/in.txt > 001-050/009/c++/out.txt
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
const ll mod = 1000000007;

ll max(ll a, ll b) {
    if (a > b) return a;
    return b;
}

void first() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
        return;
    }
    vl a(n, 0), sum(n + 1, 0);
    for (int i = 0; i < n; i++) cin >> a[i];

    sum[1] = max(a[0], 0);
    for (int i = 2; i <= n; i++)
        sum[i] = max(sum[i - 1], max(a[i - 1], sum[i - 2] + a[i - 1]));

    cout << sum[n] << endl;
}

void second() {
    int n;
    cin >> n;
    if (n == 0) {
        cout << 0 << endl;
        return;
    }
    ll cur = 0, ans = 0;

    ll a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        if (i == 0) {
            b = max(a, cur);
            continue;
        }
        ans = max(b, max(cur, a + cur));
        a = b;
        b = ans;
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        // first();
        second();
    }
}
