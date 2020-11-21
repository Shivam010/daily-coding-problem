// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #040, run using
// g++ 001-050/040/c++/code.cpp -o bin/out
// ./bin/out < 001-050/040/c++/in.txt > 001-050/040/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void nLogN() {
    int n;
    cin >> n;
    ll cur;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        mp[cur]++;
    }
    map<int, int>::iterator it = mp.begin();
    while (it != mp.end()) {
        if (it->second == 1) {
            cout << it->first << endl;
            return;
        }
        it++;
    }
}

void solve() {
    int n;
    cin >> n;
    ll cur, mask[64] = {0};
    for (int i = 0; i < n; i++) {
        cin >> cur;
        int ii = 0;
        while (cur && ii<64) {
            // as bit-by-bit summation of 3 values will be nullify
            // and the finally the ii'th bit of mask will only be
            // set if it is set in the non-duplicate number
            mask[ii] = (mask[ii] + (cur & 1)) % 3;
            ii++;
            cur >>= 1;
        }
    }
    cur = 0;
    for (ll p = 1, i = 0; i < 64; i++, p *= 2) {
        cur += p * mask[i];
    }
    cout << cur << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
