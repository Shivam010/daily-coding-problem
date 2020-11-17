// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #054, run using
// g++ 054/code.cpp -o bin/out && ./bin/out < 054/in.txt > 054/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int pow2[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

bool solve(vector<int> *board, vector<int> *check, int a, int b) {
    if (a == 8 && b == 9) return true;
    if (b == 9) return solve(board, check, a + 1, 0);
    if (board[a][b] != -1) return solve(board, check, a, b + 1);
    for (int n = 1; n < 10; n++) {
        int bl = 3 * int(a / 3) + b / 3;
        if (check[0][a] & pow2[n] || check[1][b] & pow2[n] ||
            check[2][bl] & pow2[n])
            continue;
        int tmp[3] = {check[0][a], check[1][b], check[2][bl]};
        check[0][a] |= pow2[n];
        check[1][b] |= pow2[n];
        check[2][bl] |= pow2[n];
        board[a][b] = n;
        if (solve(board, check, a, b + 1)) return true;
        board[a][b] = -1;
        check[0][a] = tmp[0];
        check[1][b] = tmp[1];
        check[2][bl] = tmp[2];
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin.ignore();
        vector<int> board[9];
        vector<int> check[3];
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) board[i].push_back(-1);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 9; j++) check[i].push_back(0);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) cin >> board[i][j];
            for (int j = 0; j < 9; j++) {
                int n = board[i][j];
                int bl = 3 * int(i / 3) + j / 3;
                check[0][i] |= pow2[n];
                check[1][j] |= pow2[n];
                check[2][bl] |= pow2[n];
            }
        }
        cout << endl << solve(board, check, 0, 0) << endl;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) cout << board[i][j] << " ";
            cout << endl;
        }
    }
}
