/*
Daily Coding Challenge #002
---------------------------
Given an array of integers, return a new array such that each element at index i
of the new array is the product of all the numbers in the original array except
the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be
[120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be
[2, 3, 6].

Follow-up: what if you can't use division?

Run Using
---------
g++ 002/code.cpp -o bin/out && ./bin/out < 002/in.txt > 002/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mk make_pair
#define pb push_back
#define Pi pair<int, int>
#define Pl pair<long long, long long>
#define vi vector<int>
#define vl vector<long long>
#define vb vector<bool>
#define vp vector<pair<int, int>>
#define vpl vector<pair<long long, long long>>
#define F first
#define S second
#define min(a, b) ((a < b) ? a : b)
const ll mod = 1000000007;

void solve() {
    ll n;
    cin >> n;
    assert(n > 1);
    vl a(n, 0), left(n, 1), right(n, 1);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    left[0] = a[0];
    for (ll i = 1; i < n; i++) {
        left[i] = 1LL * left[i - 1] * a[i];
    }
    right[n - 1] = a[n - 1];
    for (ll i = n - 2; i > -1; i--) {
        right[i] = 1LL * right[i + 1] * a[i];
    }
    cout << right[1] << " ";
    for (ll i = 1; i < n - 1; i++) {
        cout << 1LL * left[i - 1] * right[i + 1] << " ";
    }
    cout << left[n - 2] << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
