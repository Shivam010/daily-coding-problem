// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #061, run using
// g++ 051-100/061/c++/code.cpp -o bin/out
// ./bin/out < 051-100/061/c++/in.txt > 051-100/061/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll x, y, ans =1;
    cin>>x>>y;
    while(y) {
        if (y&1) ans*=x;
        y>>=1;
        x*=x;
    }
    cout<<ans<<endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
