/*
Daily Coding Challenge #047
---------------------------
This problem was asked by Facebook.

Given a array of numbers representing the stock prices of a company in
chronological order, write a function that calculates the maximum profit you
could have made from buying and selling that stock once. You must buy before you
can sell it.

For example, given [9, 11, 8, 5, 7, 10], you should return 5, since you could
buy the stock at 5 dollars and sell it at 10 dollars.

Run Using
---------
g++ 047/code.cpp -o bin/out && ./bin/out < 047/in.txt > 047/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int solutionOne(int n, int *stock) {
    int minTillNow[n];
    for (int i = 0; i < n; i++) {
        minTillNow[i] = stock[i];
        if (i > 0 && minTillNow[i - 1] < stock[i])
            minTillNow[i] = minTillNow[i - 1];
    }
    int profit = stock[1] - minTillNow[0];
    for (int i = 2; i < n; i++)
        if (profit < stock[i] - minTillNow[i - 1])
            profit = stock[i] - minTillNow[i - 1];
    return profit;
}

int solutionTwo(int n, int *stock) {
    int minPrice = stock[0], profit = stock[1] - stock[0];
    for (int i = 1; i < n; i++) {
        if (profit < stock[i] - minPrice) profit = stock[i] - minPrice;
        if (minPrice > stock[i]) minPrice = stock[i];
    }
    return profit;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        assert(n > 1);

        int stock[n];
        for (int i = 0; i < n; i++) cin >> stock[i];

        int profitOne = solutionOne(n, stock);
        int profitTwo = solutionTwo(n, stock);
        if (profitOne != profitTwo)
            cout << "error: both algo should return same profits. One: "
                 << profitOne << " Two: " << profitTwo;
        else
            cout << "Profit: " << profitOne << endl;
    }
}
