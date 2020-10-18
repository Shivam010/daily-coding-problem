/*
Daily Coding Challenge #046
---------------------------
This problem was asked by Amazon.

Given a string, find the longest palindromic contiguous substring. If there are
more than one with the maximum length, return any one.

For example, the longest palindromic substring of "aabcdcb" is "bcdcb". The
longest palindromic substring of "bananas" is "anana".

Run Using
---------
g++ 046/code.cpp -o bin/out && ./bin/out < 046/in.txt > 046/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define F first
#define S second

string solve1(string a) {
    int n = a.size();

    vector<vector<bool> > lps(n + 1, vector<bool>(n + 1, 0));
    int st = 0, en = 0;

    // single length palindrome
    for (int j = 0; j < n; j++) lps[j][j] = 1;

    // two length palindrome
    for (int j = 0; j + 1 < n; j++) {
        lps[j][j + 1] = (a[j] == a[j + 1]);
        if (lps[j][j + 1]) st = j, en = j + 1;
    }

    // d length palindrome
    for (int d = 2; d <= n; d++) {
        for (int j = 0; j + d < n; j++) {
            if (a[j] == a[j + d]) {
                lps[j][j + d] = lps[j + 1][j + d - 1];
                if (lps[j][j + d]) st = j, en = j + d;
            }
        }
    }
    return a.substr(st, en - st + 1);
}

string solve2(string a) {
    int n = a.size();

    pair<int, int> final = make_pair(0, 0), cur;
    for (int center = 0; center < n; center++) {
        // even length
        cur.F = center;
        cur.S = center + 1;
        while (cur.F >= 0 && cur.S < n && a[cur.F] == a[cur.S])
            cur.S += 1, cur.F -= 1;
        if (cur.S - cur.F > 1 && final.S - final.F < cur.S - cur.F - 2)
            final.F = cur.F + 1, final.S = cur.S - 1;

        // odd length
        cur.F = center - 1;
        cur.S = center + 1;
        while (cur.F >= 0 && cur.S < n && a[cur.F] == a[cur.S])
            cur.S += 1, cur.F -= 1;
        if (cur.S - cur.F > 2 && final.S - final.F < cur.S - cur.F - 2)
            final.F = cur.F + 1, final.S = cur.S - 1;
    }
    return a.substr(final.F, final.S - final.F + 1);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        string ans1 = solve1(a);
        string ans2 = solve2(a);
        if (ans1 != ans2)
            cout << "Different answers for the string: " << a
                 << " First: " << ans1 << " Second: " << ans2 << endl;
        else
            cout << ans1 << endl;
    }
}
