/*
Daily Coding Challenge #015
---------------------------
This problem was asked by Facebook.

Given a stream of elements too large to store in memory, pick a random element
from the stream with uniform probability.

Run Using
---------
g++ 015/code.cpp -o bin/out && ./bin/out < 015/in.txt > 015/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    srand(time(NULL));
    string n, res;
    ll cnt = 0;
    while (cin >> n) {
        cnt++;
        int rn = rand() % cnt;
        if (cnt == 1 || rn == cnt - 1) {
            res = n;
        }
        cout << res << endl;
    }
    return 0;
}
