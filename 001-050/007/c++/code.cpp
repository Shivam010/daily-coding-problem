// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #007, run using
// g++ 001-050/007/c++/code.cpp -o bin/out
// ./bin/out < 001-050/007/c++/in.txt > 001-050/007/c++/out.txt
#include <bits/stdc++.h>
using namespace std;

long long solve(string msg, int last, vector<long long> &dp) {
    if (last <= 0) return 1;
    if (dp[last] > -1) return dp[last];
    char f = msg[last - 1];
    if (last == 1) {
        dp[last] = f != '0';
        return dp[last];
    }
    char s = msg[last - 2];
    if (f != '0')
        dp[last] = solve(msg, last - 1, dp);
    else
        dp[last] = 0;

    if (s == '1' || (s == '2' && f <= '6')) {
        dp[last] += solve(msg, last - 2, dp);
    } else if (f == '0') {
        dp[last] = 0;
        return 0;
    }
    return dp[last];
};

long long minimalSol(string msg, int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    if (msg[0] == '0') return 0;
    for (int i = 2; i <= n; i++) {
        if (msg[i - 1] > '0') dp[i] = dp[i - 1];
        if (msg[i - 2] == '1' || (msg[i - 2] == '2' && msg[i - 1] < '7'))
            dp[i] += dp[i - 2];
    }
    return dp[n];
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string msg, nsg = "";
        cin >> msg;
        int n = msg.size();
        vector<long long> dp(n + 1, -1);
        cout << solve(msg, n, dp) << endl;
        cout << " " << minimalSol(msg, n) << endl;
    }
    return 0;
}