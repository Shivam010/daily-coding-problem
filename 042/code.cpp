/*
Daily Coding Challenge #042
---------------------------
This problem was asked by Google.

Given a list of integers S and a target number k, write a function that returns
a subset of S that adds up to k. If such a subset cannot be made, then return
null.

Integers can appear more than once in the list. You may assume all numbers in
the list are positive.

For example, given S = [12, 1, 61, 5, 9, 2] and k = 24, return [12, 9, 2, 1]
since it sums up to 24.

Run Using
---------
g++ 042/code.cpp -o bin/out && ./bin/out < 042/in.txt > 042/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool answer(vector<ll> &a, int n, int last, ll sum, vector<ll> &sol) {
    if (last == n || sum == 0) return sum == 0;
    if (a[last] <= sum) {
        sol.push_back(a[last]);
        if (answer(a, n, last + 1, sum - a[last], sol)) return true;
        sol.pop_back();
    }
    return answer(a, n, last + 1, sum, sol);
}

void solve() {
    int n;
    ll sum = 0;
    cin >> n >> sum;
    vector<ll> a(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), greater<ll>());
    vector<ll> sol;
    if (answer(a, n, 0, sum, sol)) {
        cout << "Yes" << endl;
        for (int i = 0; i < sol.size(); i++) {
            cout << sol[i] << " ";
        }
        cout << endl;
        return;
    }
    cout << "No" << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
