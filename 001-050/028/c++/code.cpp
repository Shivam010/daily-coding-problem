// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #028, run using
// g++ 001-050/028/c++/code.cpp -o bin/out
// ./bin/out < 001-050/028/c++/in.txt > 001-050/028/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int lmt = 1000;
vector<string> _spaces(lmt + 1, "");
string nSpaces(int n) {
    string sp = "";
    while (n > lmt) {
        sp += _spaces[lmt];
        n -= lmt;
    }
    return sp + _spaces[n];
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> str(n, "");
    vector<string> lines;
    int last = 0, len = -1;
    int spaces = 0, uneven = 0;
    for (int i = 0; i < n; i++) {
        cin >> str[i];
        int sz = str[i].size();
        if (len + sz + 1 > k) {
            spaces = uneven = 0;
            if (i - last > 1) {
                spaces = (k - len) / (i - last - 1);
                uneven = (k - len) % (i - last - 1);
            } else
                str[last] += nSpaces(k - len);
            string ln = str[last++];
            while (last != i) {
                ln += nSpaces(1 + spaces + (uneven > 0)) + str[last];
                uneven--;
                last++;
            }
            lines.push_back(ln);
            // reset
            len = -1;
            last = i;
        }
        len += sz + 1;
    }
    spaces = uneven = 0;
    if (n - last > 1) {
        spaces = (k - len) / (n - last - 1);
        uneven = (k - len) % (n - last - 1);
    } else
        str[last] += nSpaces(k - len);
    string ln = str[last++];
    while (last != n) {
        ln += nSpaces(1 + spaces + (uneven > 0)) + str[last];
        uneven--;
        last++;
    }
    lines.push_back(ln);

    n = lines.size();
    cout<<k<<endl;
    for (int i = 0; i < n; i++) cout << "\"" << lines[i] << "\"\n";
    return;
}

int main() {
    // spaces
    for (int i = 0; i < lmt + 1; i++) {
        for (int j = 0; j < i; j++) _spaces[i] += " ";
    }

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
