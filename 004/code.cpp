/*
Daily Coding Challenge #004
---------------------------
This problem was asked by Stripe.

Given an array of integers, find the first missing positive integer in linear
time and constant space. In other words, find the lowest positive integer that
does not exist in the array. The array can contain duplicates and negative
numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should
give 3.

You can modify the input array in-place.

Run Using
---------
g++ 004/code.cpp -o bin/out && ./bin/out < 004/in.txt > 004/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>

void solve() {
    int n;
    cin >> n;
    vl a;
    ll x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x > 0) a.push_back(x);
    }
    n = a.size();
    for (int i = 0; i < n; i++) {
        x = abs(a[i]);
        if (x <= n && a[x - 1] > 0) {
            a[x - 1] = -a[x - 1];
        }
    }
    ll ans = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            ans = i + 1;
            break;
        }
    }
    if (ans == -1) ans = n + 1;
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}