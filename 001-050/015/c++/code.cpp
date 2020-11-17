// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #015, run using
// g++ 015/code.cpp -o bin/out && ./bin/out < 015/in.txt > 015/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    srand(time(NULL));
    string n, res;
    ll cnt = 0;
    while (cin >> n) {
        cnt++;
        int rn = rand() % cnt;
        if (cnt == 1 || rn == cnt - 1) {
            res = n;
        }
        cout << res << endl;
    }
    return 0;
}
