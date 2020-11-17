// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #035, run using
// g++ 035/code.cpp -o bin/out && ./bin/out < 035/in.txt > 035/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solution() {
    string list;
    getline(cin, list);
    int n = list.size();
    int rEnd = 0, gEnd = 0, bEnd = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] == 'R')
            rEnd++, gEnd++, bEnd++;
        else if (list[i] == 'G')
            gEnd++, bEnd++;
        else if (list[i] == 'B')
            bEnd++;
    }
    int rStart = 0, gStart = rEnd, bStart = gEnd;
    int ri = rStart, gi = gStart, bi = bStart;
    int i = 0;
    while (i < n) {
        if (list[i] == 'R') {
            if (rStart <= i && i < rEnd)
                i++;
            else
                swap(list[ri], list[i]);
            if (i != ri) ri++;
            continue;
        }
        if (list[i] == 'G') {
            if (gStart <= i && i < gEnd)
                i++;
            else
                swap(list[gi], list[i]);
            if (i != gi) gi++;
            continue;
        }
        if (list[i] == 'B') {
            if (bStart <= i && i < bEnd)
                i++;
            else
                swap(list[bi], list[i]);
            if (i != bi) bi++;
            continue;
        }
    }
    cout<< list << endl;
}

void flush() {
    cin.clear();
    cin.ignore();
    fflush(stdin);
}

int main() {
    int t;
    cin >> t;
    flush();
    while (t--) solution();
}
