// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #010, run using
// g++ 010/code.cpp -o bin/out && time ./bin/out
*/
#include <bits/stdc++.h>
#include <time.h>
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

void wait(ll mil) {
    clock_t t = clock();
    ll clocksInMil = mil * CLOCKS_PER_SEC / 1000;
    while (clock() < clocksInMil)
        ;
}

void schedule(void fn(), ll n) {
    wait(n);
    fn();
}

void func() { printf("Shivam\n"); }

int main() { schedule(func, 5000); }
