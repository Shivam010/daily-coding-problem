// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #018, run using
// g++ 018/code.cpp -o bin/out && ./bin/out < 018/in.txt > 018/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>

void solve() {
    int n, k;
    cin >> n >> k;
    ll el;                 // element
    vl a(k, 0);            // k elements window
    vector<int> in(k, 0);  // max k elements' index
    int last = -1;         // last: iterator for a & in

    for (int i = 0; i < k; i++) {
        cin >> el;
        while (last > -1 && el > a[last]) last--;
        a[++last] = el;
        in[last] = i;
    }
    int first = 0;  // now, first is 1st element index in a & in
    cout << a[first] << " ";

    for (int i = k; i < n; i++) {
        cin >> el;
        // removing all out of window elements
        while (first != -1) {
            if (in[first] > i - k) break;
            if (first == last)
                first = last = -1;
            else
                first = (first + 1) % k;
        }

        // insert new element
        while (last != -1) {
            if (a[last] > el) break;
            if (first == last)
                first = last = -1;
            else
                last = (last - 1 + k) % k;
        }

        last = (last + 1) % k;
        if (first == -1) {
            first = last;
        }
        a[last] = el;
        in[last] = i;
        cout << a[first] << " ";
    }
    cout << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
