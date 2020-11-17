// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #027, run using
// g++ 027/code.cpp -o bin/out && ./bin/out < 027/in.txt > 027/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    string brk;
    cin >> brk;
    int n = brk.size(), top = 0;
    string stk(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (stk[top] == brk[i])
            top--;
        else if (brk[i] == '(')
            stk[++top] = ')';
        else if (brk[i] == '[')
            stk[++top] = ']';
        else if (brk[i] == '{')
            stk[++top] = '}';
        else {
            top = -1;
            break;
        }
    }
    if (top == 0)
        cout << "true\n";
    else
        cout << "false\n";
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
