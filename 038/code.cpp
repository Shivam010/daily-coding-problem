/*
Daily Coding Challenge #038
---------------------------
This problem was asked by Microsoft.

You have an N by N board. Write a function that, given N, returns the number of
possible arrangements of the board where N queens can be placed on the board
without threatening each other, i.e. no two queens share the same row, column,
or diagonal.

Run Using
---------
g++ 038/code.cpp -o bin/out && ./bin/out < 038/in.txt > 038/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vb vector<bool>
#define vi vector<int>

bool verify(int n, vb *board) {
    for (int i = 0; i < n; i++) {
        int c1 = 0, c2 = 0;
        for (int j = 0; j < n; j++) {
            c1 += board[i][j];
            c2 += board[j][i];
            if (c1 > 1 || c2 > 1) return false;
        }
        c1 = 0, c2 = 0;
        int c3 = 0, c4 = 0;
        for (int k = 0; k <= i; k++) {
            c1 += board[i - k][k];
            c2 += board[i - k][n - 1 - k];
            c3 += board[n - 1 - k][k];
            c4 += board[n - 1 - k][i - k];
            if (c1 > 1 || c2 > 1 || c3 > 1 || c4 > 1) return false;
        }
    }
    return true;
}

void print(int n, vb *board) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool nQueen(int n, vb *board, int i, vb *checks) {
    if (i == n) return true;
    for (int j = 0; j < n; j++) {
        int in = i - j;
        if (in < 0) in = n - in;
        if (checks[0][j] || checks[1][i + j] || checks[2][in]) continue;
        board[i][j] = true;
        checks[0][j] = checks[1][i + j] = checks[2][in] = true;
        // if (verify(n, board))
        if (nQueen(n, board, i + 1, checks)) return true;
        board[i][j] = false;
        checks[0][j] = checks[1][i + j] = checks[2][in] = false;
    }
    return false;
}

void solve(int n) {
    // cin >> n;
    vb board[n];
    vb checks[4];
    checks[0] = vb(n, 0);
    checks[1] = vb(n * 2, 0);
    checks[2] = vb(n * 2, 0);

    for (int i = 0; i < n; i++) board[i] = vb(n, 0);
    bool possible = nQueen(n, board, 0, checks);
    cout << n << endl;
    if (!possible) cout << "im";
    cout << "possible" << endl;
    print(n, board);
    return;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i <= t; i++) {
        solve(i);
    }
}
