/*
Daily Coding Challenge #027
---------------------------
This problem was asked by Facebook.

Given a string of round, curly, and square open and closing brackets, return
whether the brackets are balanced (well-formed).

For example, given the string `"([])[]({})"`, you should return true.

Given the string `"([)]"` or `"((()"`, you should return false.

Run Using
---------
g++ 027/code.cpp -o bin/out && ./bin/out < 027/in.txt > 027/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    string brk;
    cin >> brk;
    int n = brk.size(), top = 0;
    string stk(n + 1, 0);
    for (int i = 0; i < n; i++) {
        if (stk[top] == brk[i])
            top--;
        else if (brk[i] == '(')
            stk[++top] = ')';
        else if (brk[i] == '[')
            stk[++top] = ']';
        else if (brk[i] == '{')
            stk[++top] = '}';
        else {
            top = -1;
            break;
        }
    }
    if (top == 0)
        cout << "true\n";
    else
        cout << "false\n";
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
