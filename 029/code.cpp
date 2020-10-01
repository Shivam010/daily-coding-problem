/*
Daily Coding Challenge #029
---------------------------
This problem was asked by Amazon.

Run-length encoding is a fast and simple method of encoding strings. The basic
idea is to represent repeated successive characters as a single count and
character. For example, the string `"AAAABBBCCDAA"` would be encoded as
`"4A3B2C1D2A"`.

Implement run-length encoding and decoding. You can assume the string to be
encoded have no digits and consists solely of alphabetic characters. You can
assume the string to be decoded is valid.

Run Using
---------
g++ 029/code.cpp -o bin/out && ./bin/out < 029/in.txt > 029/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

string encode(string in) {
    string out = "", tmp;
    int n = in.size(), cnt;
    char c;
    for (int i = 0; i < n;) {
        c = in[i++];
        cnt = 1;
        while (c == in[i]) cnt++, i++;
        tmp = c;
        while (cnt) {
            c = '0' + (cnt % 10);
            tmp = c + tmp;
            cnt /= 10;
        }
        out += tmp;
    }
    return out;
}

string decode(string in) {
    string out = "", tmp;
    int n = in.size(), cnt;
    for (int i = 0; i < n; i++) {
        cnt = 0;
        while (in[i] <= '9' && in[i] >= '0') cnt = cnt * 10 + in[i] - '0', i++;
        while (cnt--) out.push_back(in[i]);
    }
    return out;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string op, str;
        cin >> op >> str;
        if (op == "enc")
            cout << str << " ::enc:: " << encode(str) << endl;
        else
            cout << str << " ::dec:: " << decode(str) << endl;
    }
}
