/*
Daily Coding Challenge #025
---------------------------
This problem was asked by Facebook.

Implement regular expression matching with the following special characters:

> `.` (period) which matches any single character
> `*` (asterisk) which matches zero or more of the preceding element

That is, implement a function that takes in a string and a valid regular
expression and returns whether or not the string matches the regular expression.

For example, given the regular expression "ra." and the string "ray", your
function should return true. The same regular expression on the string "raymond"
should return false.

Given the regular expression ".*at" and the string "chat", your function should
return true. The same regular expression on the string "chats" should return
false.

Run Using
---------
g++ 025/code.cpp -o bin/out && ./bin/out < 025/in.txt > 025/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>

bool validate(string &a, string &pat, int &n, int &pn, int i, int j, vi &ans) {
    int in = i * pn + j;
    if (ans[in]) return ans[in] == 1;
    if (i >= n && j >= pn) {
        ans[in] = 1;
        return true;
    }
    if (j + 1 < pn && pat[j + 1] == '*') {
        ans[in] = validate(a, pat, n, pn, i, j + 2, ans);
        if (ans[in] == 1) return true;
        if (i < n && (a[i] == pat[j] || pat[j] == '.')) {
            ans[in] = validate(a, pat, n, pn, i + 1, j, ans);
            if (!ans[in]) ans[in] = -1;
            return ans[in] == 1;
        }
        return false;
    }
    if (i < n && (a[i] == pat[j] || pat[j] == '.')) {
        ans[in] = validate(a, pat, n, pn, i + 1, j + 1, ans);
        if (!ans[in]) ans[in] = -1;
        return ans[in] == 1;
    }
    return false;
}

void solve() {
    string a, pat;
    cin >> a >> pat;
    if (a == "-") a = "";
    int n = a.size(), pn = pat.size();
    vi ans((n + 1) * (pn + 1), 0);  // ans -> 1 true -1 false 0 nothing
    bool res = validate(a, pat, n, pn, 0, 0, ans);
    if (a == "") a = "-";
    if (res)
        cout << a << " ::  valid for  :: " << pat << endl;
    else
        cout << a << " :: invalid for :: " << pat << endl;

    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
