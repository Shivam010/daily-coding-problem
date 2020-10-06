/*
Daily Coding Challenge #034
---------------------------
This problem was asked by Quora.

Given a string, find the palindrome that can be made by inserting the fewest
number of characters as possible anywhere in the word. If there is more than one
palindrome of minimum length that can be made, return the lexicographically
earliest one (the first one alphabetically).

For example, given the string "race", you should return "ecarace", since we can
add three letters to it (which is the smallest amount to make a palindrome).
There are seven other palindromes that can be made from "race" by adding three
letters, but "ecarace" comes first alphabetically.

As another example, given the string "google", you should return "elgoogle".

Run Using
---------
g++ 034/code.cpp -o bin/out && ./bin/out < 034/in.txt > 034/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>

int answer(string &a, int n, int i, int j, vi &ans) {
    if (i >= j) return 0;
    if (ans[i * n + j] > -1) return ans[i * n + j];
    if (a[i] == a[j]) {
        ans[i * n + j] = answer(a, n, i + 1, j - 1, ans);
        return ans[i * n + j];
    }
    int ans1 = answer(a, n, i + 1, j, ans);
    int ans2 = answer(a, n, i, j - 1, ans);
    ans[i * n + j] = 1 + ((ans1 < ans2) ? ans1 : ans2);
    return ans[i * n + j];
}

void solve() {
    string a;
    cin >> a;
    int n = a.size();
    vi ans(n * (n + 1), -1);
    cout << answer(a, n, 0, n - 1, ans) << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
