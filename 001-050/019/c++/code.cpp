// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #019, run using
// g++ 001-050/019/c++/code.cpp -o bin/out
// ./bin/out < 001-050/019/c++/in.txt > 001-050/019/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define v2 vector<vi>
#define pi pair<int, int>
#define vp vector<pi>

int rec(v2 &a, int n, int k, int in, vi &path) {
    int ai = in / k, aj = in % k;
    if (in == -1) {
        ai = -1;
        aj = -1;
    }
    if (ai > n) {
        return 0;
    }
    int ans = INT_MAX;
    int cur = ai + 1;
    if (cur == n - 1) {
        for (int i = 0; i < k; i++) {
            if (i != aj) {
                if (ans > a[cur][i]) {
                    path[cur] = i;
                    ans = a[cur][i];
                }
            }
        }
        return ans;
    }
    for (int i = 0; i < k; i++) {
        if (i != aj) {
            int x = path[cur];
            int preAns = a[cur][i] + rec(a, n, k, cur * k + i, path);
            if (ans > preAns) {
                ans = preAns;
                path[cur] = i;
            } else {
                path[cur] = x;
            }
        }
    }
    return ans;
}

void solve_one(v2 &a, int n, int k) {
    vi path(n + 1, 0);
    cout << rec(a, n, k, -1, path) << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i][path[i]] << "(" << path[i] << ") ";
    }
    cout << endl;
}

void modified(v2 &a, int n, int k) {
    vp _path(n + 1);

    pi preMin(0, -1), preSec(0, -1);

    for (int i = 0; i < n; i++) {
        pi curMin(INT_MAX, -1), curSec(INT_MAX, -1);
        // cout << preMin.first << " " << preMin.second << endl;

        for (int j = 0; j < k; j++) {
            if (preMin.second != j)  // different index -> can have same color
                a[i][j] += preMin.first;
            else  // same index -> must have different color
                a[i][j] += preSec.first;

            if (curMin.first > a[i][j]) {
                swap(curMin, curSec);
                curMin.first = a[i][j];
                curMin.second = j;
            } else if (curSec.first > a[i][j]) {
                curSec.first = a[i][j];
                curSec.second = j;
            }
        }

        _path[i].first = curMin.second;
        _path[i].second = curSec.second;
        if (preMin.second == _path[i].first)
            swap(_path[i].first, _path[i].second);

        swap(preMin, curMin);
        swap(preSec, curSec);
    }

    cout << preMin.first << endl;
    vi path(n, 0);
    path[n - 1] = _path[n - 1].first;
    for (int i = n - 2; i >= 0; i--) {
        path[i] = _path[i].first;
        if (path[i + 1] == path[i]) path[i] = _path[i].second;
    }

    int pre = 0;
    for (int i = 0; i < n; i++) {
        a[i][path[i]]-=pre;
        pre += a[i][path[i]];
        cout << a[i][path[i]] << "(" << path[i] << ") ";
    }

    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        v2 a(n, vi(k, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) cin >> a[i][j];
        }
        // solve_one(a, n, k);
        modified(a, n, k);
    }
}
