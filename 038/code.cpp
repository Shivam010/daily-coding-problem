/*
Daily Coding Challenge #038
---------------------------
This problem was asked by Microsoft.

You have an `N by N` board. Write a function that, given `N`, returns the number
of possible arrangements of the board where N queens can be placed on the board
without threatening each other, i.e. no two queens share the same row, column,
or diagonal.

Run Using
---------
g++ 038/code.cpp -o bin/out && ./bin/out < 038/in.txt > 038/out.txt
*/
#include <bits/stdc++.h>
using namespace std;

bool verify(vector<int> queenPos) {
    int last = queenPos.size() - 1;
    int lastPos = queenPos[last];
    for (int i = 0; i < last; i++) {
        int cur = queenPos[i];
        int dist = last - i;
        if (dist < 0) dist = -dist;
        if (cur == lastPos || cur + dist == lastPos || cur - dist == lastPos)
            return false;
    }
    return true;
}

void print(int n, vector<int> queenPos) {
    n = queenPos.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < queenPos[i]; j++) cout << "• ";
        cout << "Q ";
        for (int j = queenPos[i] + 1; j < n; j++) cout << "• ";
        cout << endl;
    }
}

int nQueen(int n, vector<int> &queenPos, vector<int> &final) {
    if (n == queenPos.size()) return 1;
    int cnt = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        queenPos.push_back(i);
        if (verify(queenPos)) {
            cur = nQueen(n, queenPos, final);
            if (cur && final.size() == 0)
                for (int k = 0; k < n; k++) final.push_back(queenPos[k]);
            cnt += cur;
        }
        queenPos.pop_back();
    }
    return cnt;
}

void solve(int n) {
    // cin >> n;
    vector<int> queenPos, final;
    int cnt = nQueen(n, queenPos, final);
    cout << cnt << " Possible for " << n << endl;
    print(n, final);
    return;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i <= t; i++) {
        solve(i);
    }
}
