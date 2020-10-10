/*
Daily Coding Challenge #035
---------------------------
This problem was asked by Google.

Given an array of strictly the characters 'R', 'G', and 'B', segregate the
values of the array so that all the Rs come first, the Gs come second, and the
Bs come last. You can only swap elements of the array.

Do this in linear time and in-place.

For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should
become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].

Run Using
---------
g++ 035/code.cpp -o bin/out && ./bin/out < 035/in.txt > 035/out.txt
*/
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
