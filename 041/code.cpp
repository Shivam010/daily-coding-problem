/*
Daily Coding Challenge #041
---------------------------
This problem was asked by Facebook.

Given an unordered list of flights taken by someone, each represented as
(origin, destination) pairs, and a starting airport, compute the person's
itinerary. If no such itinerary exists, return null. If there are multiple
possible itineraries, return the lexicographically smallest one. All flights
must be used in the itinerary.

For example, given the list of flights [('SFO', 'HKO'), ('YYZ', 'SFO'), ('YUL',
'YYZ'), ('HKO', 'ORD')] and starting airport 'YUL', you should return the list
['YUL', 'YYZ', 'SFO', 'HKO', 'ORD'].

Given the list of flights [('SFO', 'COM'), ('COM', 'YYZ')] and starting airport
'COM', you should return null.

Given the list of flights [('A', 'B'), ('A', 'C'), ('B', 'C'), ('C', 'A')] and
starting airport 'A', you should return the list ['A', 'B', 'C', 'A', 'C'] even
though ['A', 'C', 'A', 'B', 'C'] is also a valid itinerary. However, the first
one is lexicographically smaller.

Run Using
---------
g++ 041/code.cpp -o bin/out && ./bin/out < 041/in.txt > 041/out.txt
*/
#include <bits/stdc++.h>
using namespace std;

bool backtrack(int n, int noUsed, pair<string, string> *list, bool *used,
               string *it) {
    if (noUsed == n) return true;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        if (it[noUsed] == list[i].first) {
            used[i] = true;
            it[++noUsed] = list[i].second;
            if (backtrack(n, noUsed, list, used, it)) return true;
            noUsed--;
            used[i] = false;
        }
    }

    return false;
}

void solve() {
    int n, sz = 0;
    cin >> n;
    pair<string, string> list[n];
    bool used[n];
    for (int i = 0; i < n; i++) {
        cin >> list[i].first >> list[i].second;
        used[i] = false;
    }
    sort(list, list + n);

    string it[n + 1];
    cin >> it[0];
    if (backtrack(n, 0, list, used, it))
        for (int i = 0; i <= n; i++) cout << it[i] << " ";
    else
        cout << -1;
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    fflush(stdin);
    cin.ignore();
    while (t--) {
        solve();
    }
}
