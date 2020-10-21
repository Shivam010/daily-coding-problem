/*
Daily Coding Challenge #049
---------------------------
This problem was asked by Amazon.

Given an array of numbers, find the maximum sum of any contiguous subarray of
the array.

For example, given the array `[34, -50, 42, 14, -5, 86]`, the maximum sum would
be `137`, since we would take elements `42, 14, -5, and 86`.

Given the array `[-5, -1, -8, -9]`, the maximum sum would be `0`, since we would
not take any elements.

Do this in `O(N)` time.

Run Using
---------
g++ 049/code.cpp -o bin/out && ./bin/out < 049/in.txt > 049/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solution() {
    int n;
    cin >> n;
    ll sum = 0, curSum = 0, ele = 0;
    for (int i = 0; i < n; i++) {
        cin >> ele;
        if (curSum + ele >= 0)
            curSum += ele;
        else
            curSum = 0;
        if (curSum > sum) sum = curSum;
    }
    cout << sum << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solution();
    }
}
