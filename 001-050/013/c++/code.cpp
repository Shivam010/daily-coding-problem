// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #013, run using
// g++ 001-050/013/c++/code.cpp -o bin/out
// ./bin/out < 001-050/013/c++/in.txt > 001-050/013/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>

void solve() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = s.size();
    if (n < k || k <= 0) {
        cout << 0 << endl;
        return;
    }
    vi mp(26, false);
    int st = 0, cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (!mp[c]) cnt++;
        mp[c]++;
        if (cnt < k) continue;
        if (cnt == k && ans < i - st + 1) {
            ans = i - st + 1;
            continue;
        }
        while (st <= i && cnt > k) {
            c = s[st] - 'a';
            mp[c]--;
            if (!mp[c]) cnt--;
            st++;
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
