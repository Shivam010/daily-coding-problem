/*
Daily Coding Challenge #037
---------------------------
This problem was asked by Google.

The power set of a set is the set of all its subsets. Write a function that,
given a set, generates its power set.

For example, given the set `{1, 2, 3}`, it should return `{{}, {1}, {2}, {3},
{1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}`

You may also use a list or array to represent a set.

Run Using
---------
g++ 037/code.cpp -o bin/out && ./bin/out < 037/in.txt > 037/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solution() {
    int n;
    cin >> n;
    ll a[n], mask[n];
    mask[n] = 1 << n;
    for (int i = 0; i < n; i++) cin >> a[i], mask[i] = 1 << i;
    ll sz = 1 << n;
    cout << n << endl;
    while (sz--) {
        cout << "{";
        bool comma = false;
        for (int i = 0; i < n; i++) {
            if (sz & mask[i]) {
                if (comma) cout << ",";
                cout << a[i];
                comma = true;
            }
        }
        cout << "}\n";
    }
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solution();
    }
}
