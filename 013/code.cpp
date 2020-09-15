/*
Daily Coding Challenge #013
---------------------------
This problem was asked by Amazon.

Given an integer k and a string s, find the length of the longest substring that
contains at most k distinct characters.

For example, given s = "abcba" and k = 2, the longest substring with k distinct
characters is "bcb".

Run Using
---------
g++ 013/code.cpp -o bin/out && ./bin/out < 013/in.txt > 013/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>

void solve() {
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = s.size();
    if (n < k || k <= 0) {
        cout << 0 << endl;
        return;
    }
    vi mp(26, false);
    int st = 0, cnt = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (!mp[c]) cnt++;
        mp[c]++;
        if (cnt < k) continue;
        if (cnt == k && ans < i - st + 1) {
            ans = i - st + 1;
            continue;
        }
        while (st <= i && cnt > k) {
            c = s[st] - 'a';
            mp[c]--;
            if (!mp[c]) cnt--;
            st++;
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
