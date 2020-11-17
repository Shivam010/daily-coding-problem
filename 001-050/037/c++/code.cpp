// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #037, run using
// g++ 001-050/037/c++/code.cpp -o bin/out
// ./bin/out < 001-050/037/c++/in.txt > 001-050/037/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solution() {
    int n;
    cin >> n;
    ll a[n], mask[n];
    mask[n] = 1 << n;
    for (int i = 0; i < n; i++) cin >> a[i], mask[i] = 1 << i;
    ll sz = 1 << n;
    cout << n << endl;
    while (sz--) {
        cout << "{";
        bool comma = false;
        for (int i = 0; i < n; i++) {
            if (sz & mask[i]) {
                if (comma) cout << ",";
                cout << a[i];
                comma = true;
            }
        }
        cout << "}\n";
    }
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solution();
    }
}
