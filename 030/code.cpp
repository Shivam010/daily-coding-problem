/*
Daily Coding Challenge #030
---------------------------
This problem was asked by Facebook.

You are given an array of non-negative integers that represents a
two-dimensional elevation map where each element is unit-width wall and the
integer is the height. Suppose it will rain and all spots between two walls get
filled up.

Compute how many units of water remain trapped on the map in `O(N)` time and
`O(1)` space.

For example, given the input `[2, 1, 2]`, we can hold `1 unit` of water in the
middle.

Given the input `[3, 0, 1, 3, 0, 5]`, we can hold `3 units` in the first index,
`2` in the second, and `3` in the fourth index (we cannot hold `5` since it
would run off to the left), so we can trap `8` units of water.

Run Using
---------
g++ 030/code.cpp -o bin/out && ./bin/out < 030/in.txt > 030/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    int n;
    cin >> n;
    vector<ll> wall(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> wall[i];
    }
    ll ans = 0, mxSt = 0, mxEn = 0;
    int st = 0, en = n - 1;
    while (st <= en) {
        if (wall[st] < wall[en]) {
            if (mxSt <= wall[st])
                mxSt = wall[st];
            else
                ans += mxSt - wall[st];
            st++;
        } else {
            if (mxEn <= wall[en])
                mxEn = wall[en];
            else
                ans += mxEn - wall[en];
            en--;
        }
    }
    cout << ans << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
