/*
Daily Coding Challenge #033
---------------------------
This problem was asked by Microsoft.

Compute the running median of a sequence of numbers. That is, given a stream of
numbers, print out the median of the list so far on each new element.

Recall that the median of an even-numbered list is the average of the two middle
numbers.

For example, given the sequence `[2, 1, 5, 7, 2, 0, 5]`, your algorithm should
print out:

```
2
1.5
2
3.5
2
2
2
```

Run Using
---------
g++ 033/code.cpp -o bin/out && ./bin/out < 033/in.txt > 033/out.txt
g++ 033/code.cpp -o bin/out && ./bin/out < 033/in01.txt > 033/out01.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>

void heapify(vi &hp, bool comp(int a, int b)) {
    int n = hp.size();
    int in = n - 1, br = 1;
    while (in > 0 && br) {
        br = 0;
        int cur = in, root = (in - 1) / 2;
        if (comp(hp[in], hp[root])) in = root, br++;
        if (br) swap(hp[in], hp[cur]);
    }
}

void popify(vi &hp, bool comp(int a, int b)) {
    int n = hp.size();
    int in = 0, br = 1;
    while (in < n && br) {
        br = 0;
        int cur = in, left = 2 * in + 1, right = 2 * in + 2;
        if (left < n && comp(hp[left], hp[in])) in = left, br++;
        if (right < n && comp(hp[right], hp[in])) in = right, br++;
        if (br) swap(hp[in], hp[cur]);
    }
}

bool upComp(int a, int b) { return a > b; }
bool lowComp(int a, int b) { return a < b; }

// up -> max heap
// low -> min heap
void solve(int n, vi &up, vi &low) {
    up.push_back(n);
    heapify(up, upComp);

    cout << "-> " << n << "\n\tmedian: ";
    int upLen = up.size(), lowLen = low.size();

    if (upLen == lowLen + 2 || (lowLen && up[0] > low[0])) {
        // pop from up
        int el = up[0];
        up[0] = up[upLen - 1];
        up.pop_back();
        popify(up, upComp);
        // push in low
        low.push_back(el);
        heapify(low, lowComp);
        upLen = up.size(), lowLen = low.size();
    }

    if (upLen == lowLen + 1) {
        cout << up[0] << endl;
        return;
    }
    if (lowLen == upLen + 1) {
        cout << low[0] << endl;
        return;
    }
    if (lowLen == upLen + 2) {
        // pop from low
        int el = low[0];
        low[0] = low[lowLen - 1];
        low.pop_back();
        popify(low, lowComp);
        // push in up
        up.push_back(el);
        heapify(up, upComp);
        upLen = up.size(), lowLen = low.size();
    }

    cout << (low[0] + up[0]) / 2.0 << endl;
    return;
}

int main() {
    int n;
    vi up, low;
    while (cin >> n) solve(n, up, low);
}
