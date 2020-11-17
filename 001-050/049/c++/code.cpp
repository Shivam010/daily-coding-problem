// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #049, run using
// g++ 049/code.cpp -o bin/out && ./bin/out < 049/in.txt > 049/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solution() {
    int n;
    cin >> n;
    ll sum = 0, curSum = 0, ele = 0;
    for (int i = 0; i < n; i++) {
        cin >> ele;
        if (curSum + ele >= 0)
            curSum += ele;
        else
            curSum = 0;
        if (curSum > sum) sum = curSum;
    }
    cout << sum << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solution();
    }
}
