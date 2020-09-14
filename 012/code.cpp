/*
Daily Coding Challenge #012
---------------------------
This problem was asked by Amazon.

There exists a staircase with N steps, and you can climb up either 1 or 2 steps
at a time. Given N, write a function that returns the number of unique ways you
can climb the staircase. The order of the steps matters.

For example, if N is 4, then there are 5 unique ways:

    1, 1, 1, 1
    2, 1, 1
    1, 2, 1
    1, 1, 2
    2, 2

What if, instead of being able to climb 1 or 2 steps at a time, you could climb
any number from a set of positive integers X? For example, if X = {1, 3, 5}, you
could climb 1, 3, or 5 steps at a time.

Run Using
---------
g++ 012/code.cpp -o bin/out && ./bin/out < 012/in.txt > 012/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vl vector<ll>
vl sol(1000000, -1);

ll solve(ll n, vl &list) {
    if (sol[n] != -1) return sol[n];
    ll len = list.size();
    if (n <= 0 || len == 0) {
        sol[n] = 0;
        return 0;
    }
    if (len == 1) {
        sol[n] = (n / list[0]) * (n % list[0] == 0);
        return sol[n];
    }
    ll ans = 0;

    for (ll i = 0; i < len; i++) {
        if (list[i] > n) continue;
        if (n - list[i] == 0) {
            ans += 1;
            continue;
        }
        ans += solve(n - list[i], list);
    }
    sol[n] = ans;
    return ans;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        sol.clear();
        sol = vl(1000000, -1);
        ll n, noSteps;
        cin >> n >> noSteps;
        vl list(noSteps, 0);
        for (ll i = 0; i < noSteps; i++) {
            cin >> list[i];
        }
        sort(list.begin(), list.end());
        cout << solve(n, list) << endl;
    }
}
