// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #012, run using
// g++ 001-050/012/c++/code.cpp -o bin/out
// ./bin/out < 001-050/012/c++/in.txt > 001-050/012/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
vl sol(1000000, -1);

ll solve(ll n, vl &list) {
    if (sol[n] != -1) return sol[n];
    ll len = list.size();
    if (n <= 0 || len == 0) {
        sol[n] = 0;
        return 0;
    }
    if (len == 1) {
        sol[n] = (n / list[0]) * (n % list[0] == 0);
        return sol[n];
    }
    ll ans = 0;

    for (ll i = 0; i < len; i++) {
        if (list[i] > n) continue;
        if (n - list[i] == 0) {
            ans += 1;
            continue;
        }
        ans += solve(n - list[i], list);
    }
    sol[n] = ans;
    return ans;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        sol.clear();
        sol = vl(1000000, -1);
        ll n, noSteps;
        cin >> n >> noSteps;
        vl list(noSteps, 0);
        for (ll i = 0; i < noSteps; i++) {
            cin >> list[i];
        }
        sort(list.begin(), list.end());
        cout << solve(n, list) << endl;
    }
}
