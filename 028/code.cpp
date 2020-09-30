/*
Daily Coding Challenge #028
---------------------------
This problem was asked by Palantir.

Write an algorithm to justify text. Given a sequence of words and an integer
line length `k`, return a list of strings which represents each line, fully
justified.

More specifically, you should have as many words as possible in each line. There
should be at least one space between each word. Pad extra spaces when necessary
so that each line has exactly length k. Spaces should be distributed as equally
as possible, with the extra spaces, if any, distributed starting from the left.

If you can only fit one word on a line, then you should pad the right-hand side
with spaces.

Each word is guaranteed not to be longer than k.

For example, given the list of words `["the", "quick", "brown", "fox", "jumps",
"over", "the", "lazy", "dog"]` and `k = 16`, you should return the following:

```
["the  quick brown", # 1 extra space on the left
"fox  jumps  over", # 2 extra spaces distributed evenly
"the   lazy   dog"] # 4 extra spaces distributed evenly
```

Run Using
---------
g++ 028/code.cpp -o bin/out && ./bin/out < 028/in.txt > 028/out.txt
*/
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
