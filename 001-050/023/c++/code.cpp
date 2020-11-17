// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #023, run using
// g++ 023/code.cpp -o bin/out && ./bin/out < 023/in.txt > 023/out.txt
#include <bits/stdc++.h>
#define vi vector<int>
#define vb vector<bool>
#define vb2 vector<vector<bool> >
#define pa pair<int, int>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    vi mat(n * m + 1, -1);
    char c = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c;
            mat[i * m + j] = (c == 'f');
            // cout << i * m + j << " ";
        }
        // cout << endl;
    }

    int sti, stj, eni, enj;
    cin >> sti >> stj >> eni >> enj;
    int st = sti * m + stj;
    int en = eni * m + enj;

    priority_queue<pa, vector<pa>, greater<pa> > pq;

    pq.push(make_pair(0, st));

    while (!pq.empty()) {
        pa val = pq.top();
        int in = val.second, dis = val.first;
        if (in == en) {
            cout << dis << endl;
            return;
        }
        pq.pop();
        while (!pq.empty() && pq.top().second == in) pq.pop();
        mat[in] = 2;

        if (in % m != m - 1 && mat[in + 1] == 1) {
            pq.push(make_pair(dis + 1, in + 1));
        }
        if (in % m != 0 && mat[in - 1] == 1) {
            pq.push(make_pair(dis + 1, in - 1));
        }
        if (in <= n * m - 1 - m && mat[in + m] == 1) {
            pq.push(make_pair(dis + 1, in + m));
        }
        if (in >= m && mat[in - m] == 1) {
            pq.push(make_pair(dis + 1, in - m));
        }
    }
    cout << -1 << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
