/*
Daily Coding Challenge #032
---------------------------
This problem was asked by Jane Street.

Suppose you are given a table of currency exchange rates, represented as a `2D
array`. Determine whether there is a possible arbitrage: that is, whether there
is some sequence of trades you can make, starting with some amount A of any
currency, so that you can end up with some amount greater than A of that
currency.

There are no transaction costs and you can trade fractional quantities.

  a b c
a 0 2 1
b 2 0 5
c 1 3 0

1c
c-a 1c - 1a
a-b 1a - 2b
b-c 2b - 10c
10c


Run Using
---------
g++ 032/code.cpp -o bin/out && ./bin/out < 032/in.txt > 032/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vf vector<float>

void solve() {
    int n;
    float x;
    cin >> n;
    vf tra[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> x;
            tra[i].push_back(x);
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tra[i][j] < tra[i][k] * tra[k][j]) {
                    tra[i][j] = tra[i][k] * tra[k][j];
                }
                if (i == j && tra[i][j] > 1) {
                    cout << "Yes" << endl;
                    return;
                }
            }
        }
    }
    cout << "No" << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
