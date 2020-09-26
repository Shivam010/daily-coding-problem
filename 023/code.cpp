/*
Daily Coding Challenge #023
---------------------------
This problem was asked by Google.

You are given an `M by N` matrix consisting of booleans that represents a board.
Each True boolean represents a wall. Each False boolean represents a tile you
can walk on.

Given this matrix, a start coordinate, and an end coordinate, return the minimum
number of steps required to reach the end coordinate from the start. If there is
no possible path, then return null. You can move up, left, down, and right. You
cannot move through walls. You cannot wrap around the edges of the board.

For example, given the following board:

```
[[f, f, f, f],
[t, t, f, t],
[f, f, f, f],
[f, f, f, f]]
```

and start = (3, 0) (bottom left) and end = (0, 0) (top left), the minimum number
of steps required to reach the end is 7, since we would need to go through (1,
2) because there is a wall everywhere else on the second row.

Run Using
---------
g++ 023/code.cpp -o bin/out && ./bin/out < 023/in.txt > 023/out.txt
*/
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
