// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #042, run using
// g++ 001-050/042/c++/code.cpp -o bin/out
// ./bin/out < 001-050/042/c++/in.txt > 001-050/042/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool answer(vector<ll> &a, int n, int last, ll sum, vector<ll> &sol) {
    if (last == n || sum == 0) return sum == 0;
    if (a[last] <= sum) {
        sol.push_back(a[last]);
        if (answer(a, n, last + 1, sum - a[last], sol)) return true;
        sol.pop_back();
    }
    return answer(a, n, last + 1, sum, sol);
}

void solve() {
    int n;
    ll sum = 0;
    cin >> n >> sum;
    vector<ll> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), greater<ll>());
    vector<ll> sol;
    if (answer(a, n, 0, sum, sol)) {
        cout << "Yes" << endl;
        for (int i = 0; i < sol.size(); i++) {
            cout << sol[i] << " ";
        }
        cout << endl;
        return;
    }
    cout << "No" << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
