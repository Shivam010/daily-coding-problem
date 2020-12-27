// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge Other#003, run using
// g++ other/003/code.cpp -o bin/out
// ./bin/out < other/003/in.txt > other/003/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll mod = (1000000007);

/*
1
2 2 2
1 2

> 500000001
*/

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll p = pow(a, b / 2) % mod;
    p = (1LL * p * p) % mod;
    if (b & 1) return (1LL * p * a) % mod;
    return p;
}
ll inverse(ll a) { return pow(a, mod - 2); }

int noOfSetBits(int n) {
    int cnt = 0;
    while (n) {
        n = n & (n - 1);
        cnt++;
    }
    return cnt;
}

void solve() {
    int n;
    ll o, e;
    cin >> n >> o >> e;
    ll invO = inverse(o);
    ll invE = inverse(e);
    assert(1 <= n && n <= 16);
    ll a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = a[i] % mod;
    }
    ll ans = 0;          // final answer
    ll cnt = pow(2, n);  // no. of subsets
    ll add, mul;         // for o and e
    while (--cnt) {
        ll x = cnt;
        int size = noOfSetBits(x);  // size of current subset;
        add = e;
        mul = invO;
        if (size & 1) {  // odd; use reverse
            add = o;
            mul = invE;
        }
        ll val = mul, i = 0;
        while (x) {
            if (x & 1)
                val = (val * (a[i] + add) % mod) % mod;  // apply coditions
            i++;
            x >>= 1;
        }
        // cout << val << " ";
        ans = ans ^ val;
    }
    // cout << endl;
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
