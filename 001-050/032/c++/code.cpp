// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #032, run using
// g++ 032/code.cpp -o bin/out && ./bin/out < 032/in.txt > 032/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vf vector<float>

void solve() {
    int n;
    float x;
    cin >> n;
    vf tra[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> x;
            tra[i].push_back(x);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tra[i][j] < tra[i][k] * tra[k][j]) {
                    tra[i][j] = tra[i][k] * tra[k][j];
                }
                if (i == j && tra[i][j] > 1) {
                    cout << "Yes" << endl;
                    return;
                }
            }
        }
    }
    cout << "No" << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
