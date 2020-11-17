// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #014, run using
// g++ 014/code.cpp -o bin/out && ./bin/out < 014/in.txt > 014/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll LIMIT = 100000007;

int main() {
    double cnt = 0, x = 0, y = 0;
    for (ll i = 0; i < LIMIT; i++) {
        x = double(rand()) / double(RAND_MAX);
        y = double(rand()) / double(RAND_MAX);
        // cout << x << " " << y << endl;
        if (x * x + y * y <= 1) cnt++;
    }
    // probability that x,y is in first quadrant = (π*1*1/4)/1*1 = π/4
    // => π/4 = cnt/LIMIT
    double pi = cnt * 4.0 / (LIMIT);
    cout << "Value of pi " << pi << endl;
}
