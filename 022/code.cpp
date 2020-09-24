/*
Daily Coding Challenge #022
---------------------------
This problem was asked by Microsoft.

Given a dictionary of words and a string made up of those words (no spaces),
return the original sentence in a list. If there is more than one possible
reconstruction, return any of them. If there is no possible reconstruction, then
return null.

For example, given the set of words 'quick', 'brown', 'the', 'fox', and the
string "thequickbrownfox", you should return ['the', 'quick', 'brown', 'fox'].

Given the set of words 'bed', 'bath', 'bedbath', 'and', 'beyond', and the string
"bedbathandbeyond", return either ['bed', 'bath', 'and', 'beyond] or ['bedbath',
'and', 'beyond'].

Run Using
---------
g++ 022/code.cpp -o bin/out && ./bin/out < 022/in.txt > 022/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vs vector<string>
#define hash(n, i, j) ((i * n + j))

vs answer(vs *dp, vs &dic, string &word, int st, int n, int dicLen) {
    if (dp[st].size() > 0) {
        return dp[st];
    }
    vs res;
    string tmp = "";
    for (int j = st; j < n; j++) {
        bool found = false;
        tmp.push_back(word[j]);
        for (int i = 0; i < dicLen; i++) {
            if (dic[i] == tmp) {
                found = true;
                break;
            }
        }
        if (found) {
            if (j == n - 1) {
                res.push_back(tmp);
                dp[st] = res;
                return res;
            }
            res = answer(dp, dic, word, j + 1, n, dicLen);
            if (res.size() > 0) {
                res.push_back(tmp);
                dp[st] = res;
                return res;
            }
        }
    }
    dp[st] = res;
    return res;
}

void solve() {
    int dicLen;
    cin >> dicLen;
    fflush(stdin);
    vs dic(dicLen, "");
    for (int i = 0; i < dicLen; i++) {
        cin >> dic[i];
    }
    string word;
    cin >> word;
    int n = word.size();
    vs dp[n + 1];
    vs ans = answer(dp, dic, word, 0, n, dicLen);
    n = ans.size();
    if (n == 0) {
        cout << "-\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
