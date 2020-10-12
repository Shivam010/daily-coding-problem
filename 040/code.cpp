/*
Daily Coding Challenge #040
---------------------------
This problem was asked by Google.

Given an array of integers where every integer occurs three times except for one
integer, which only occurs once, find and return the non-duplicated integer.

For example, given [6, 1, 3, 3, 3, 6, 6], return 1. Given [13, 19, 13, 13],
return 19.

Do this in O(N) time and O(1) space.

Run Using
---------
g++ 040/code.cpp -o bin/out && ./bin/out < 040/in.txt > 040/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void nLogN() {
    int n;
    cin >> n;
    ll cur;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        mp[cur]++;
    }
    map<int, int>::iterator it = mp.begin();
    while (it != mp.end()) {
        if (it->second == 1) {
            cout << it->first << endl;
            return;
        }
        it++;
    }
}

void solve() {
    int n;
    cin >> n;
    ll cur, mask[64] = {0};
    for (int i = 0; i < n; i++) {
        cin >> cur;
        int ii = 0;
        while (cur) {
            // as bit-by-bit summation of 3 values will be nullify
            // and the finally the ii'th bit of mask will only be
            // set if it is set in the non-duplicate number
            mask[ii] = (mask[ii] + (cur & 1)) % 3;
            ii++;
            cur >>= 1;
        }
    }
    cur = 0;
    for (ll p = 1, i = 0; i < 64; i++, p *= 2) {
        cur += p * mask[i];
    }
    cout << cur << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        nLogN();
    }
}
