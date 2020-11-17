// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #039, run using
// g++ 039/code.cpp -o bin/out && ./bin/out < 039/in.txt > 039/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define pa pair<int, int>
#define vp vector<pa>

struct Game {
    int cells;
    vp points;

    Game() {
        cin >> cells;
        points = vp(cells, mk(0, 0));
        for (int i = 0; i < cells; i++)
            cin >> points[i].first >> points[i].second;
        sort(points.begin(), points.end());
    }
    Game(int n, vp &cor) {
        cells = n;
        points = cor;
        sort(points.begin(), points.end());
    }
    int liveNeighbours(int ii) {
        int cnt = 0;
        pa cur = points[ii];
        for (int i = 0; i < cells; i++) {
            if (i == ii) continue;
            pa nx = points[i];
            if (cur.first + 1 < nx.first) break;
            if (cur.first - 1 > nx.first || cur.second - 1 > nx.second ||
                cur.second + 1 < nx.second)
                continue;
            cnt++;
        }
        return cnt;
    }
    void Print() {
        if (cells == 0) {
            cout << "First cell: 0 0\n";
            cout << "Last cell: 0 0\n";
            cout << "." << endl;
            return;
        }
        pa mn = pa(points[0]);
        pa mx = pa(points[0]);
        // cout << points[0].first << " " << points[0].second << endl;
        for (int i = 1; i < cells; i++) {
            if (points[i].first > mx.first)
                mx.first = points[i].first;
            else if (points[i].first < mn.first)
                mn.first = points[i].first;
            if (points[i].second > mx.second)
                mx.second = points[i].second;
            else if (points[i].second < mn.second)
                mn.second = points[i].second;
            // points
            // cout << points[i].first << " " << points[i].second << endl;
        }

        cout << "First cell: " << mn.first << " " << mn.second << endl;
        cout << "Last cell: " << mx.first << " " << mx.second << endl;

        // print
        int xLen = mx.first - mn.first + 1;
        int yLen = mx.second - mn.second + 1;
        string lane = ". ";
        int i = 1;
        while (i * 2 < yLen) lane += lane, i *= 2;
        while (i < yLen) lane += ". ", i++;
        vector<string> board(xLen, lane);

        for (int i = 0; i < cells; i++)
            board[points[i].first - mn.first]
                 [2 * (points[i].second - mn.second)] = '*';

        cout << "   ";
        for (int i = 0; i < yLen; i++) cout << i + mn.second << " ";
        cout << endl;
        for (int i = 0; i < xLen; i++) {
            cout << setw(2) << i + mn.first << " " << board[i] << endl;
        }
    }

    void Play(int steps) {
        for (int i = 0; i < steps; i++) {
            vp cors;
            map<pa, int> neighHealths;

            // murder unhealth points
            for (int ii = 0; ii < cells; ii++) {
                pa cur = points[ii];
                int health = liveNeighbours(ii);
                if (health == 2 || health == 3) cors.push_back(cur);
                // increase health of neighbours
                neighHealths[mk(cur.first - 1, cur.second - 1)]++;
                neighHealths[mk(cur.first - 1, cur.second)]++;
                neighHealths[mk(cur.first - 1, cur.second + 1)]++;
                neighHealths[mk(cur.first, cur.second - 1)]++;
                neighHealths[mk(cur.first, cur.second + 1)]++;
                neighHealths[mk(cur.first + 1, cur.second - 1)]++;
                neighHealths[mk(cur.first + 1, cur.second)]++;
                neighHealths[mk(cur.first + 1, cur.second + 1)]++;
            }
            // incarnate healthy neighbours
            map<pa, int>::iterator it;
            for (it = neighHealths.begin(); it != neighHealths.end(); it++)
                if (it->second == 3) cors.push_back(it->first);

            points.clear();
            if (cors.size() > 0) {
                sort(cors.begin(), cors.end());
                points.push_back(cors[0]);
                int n = cors.size();
                for (int p = 0, i = 1; i < n; i++) {
                    if (cors[p] != cors[i]) {
                        points.push_back(cors[i]);
                        p = i;
                    }
                }
            }
            cells = points.size();
            // print
            cout << "\nAfter Step " << i + 1 << endl;
            Print();
        }
    }
};

void solve() {
    Game *game = new Game();
    cout << "Initial state 0\n";
    cout << "---------------\n";
    game->Print();
    int steps;
    cin >> steps;
    game->Play(steps);
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
