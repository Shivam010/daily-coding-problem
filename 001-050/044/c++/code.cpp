// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #044, run using
// g++ 001-050/044/c++/code.cpp -o bin/out
// ./bin/out < 001-050/044/c++/in.txt > 001-050/044/c++/out.txt
#include <iostream>
using namespace std;

int usingBIT(int *a, int n) {
    int mx = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (mx < a[i]) mx = a[i];
        assert(a[i] > 0);
    }
    int bit[mx + 1];
    for (int i = 0; i <= mx; i++) bit[i] = 0;
    int ans = 0;
    for (int in, i = 0; i < n; i++) {
        // no. of elements bigger than a(i) i.e. x = a(i); ans = sum[x..mx]
        in = a[i] + 1;
        while (in <= mx) {
            ans += bit[in];
            in += (in & (-in));
        }
        in = a[i];
        while (in > 0) {
            bit[in]++;
            in -= (in & (-in));
        }
    }
    return ans;
}

void swap(int &a, int &b) {
    int t = a;
    b = a;
    a = t;
}

int merge(int *a, int n) {
    int l = n / 2, r = n;
    int i = 0, j = l;
    int k = 0, inv = 0;
    int arr[n];
    while (i < l && j < r) {
        if (a[i] <= a[j])
            arr[k++] = a[i++];
        else if (a[i] > a[j])
            arr[k++] = a[j++], inv += (l - i);
    }
    while (i < l) arr[k++] = a[i++];
    while (j < r) arr[k++] = a[j++];
    i = 0;
    while (i < n) a[i] = arr[i], i++;
    return inv;
}

int usingMergeSort(int *a, int n) {
    if (n <= 1) return 0;
    int inv = 0;
    if (n == 2) {
        if (a[0] > a[1]) swap(a[0], a[1]), inv = 1;
        return inv;
    }
    inv += usingMergeSort(a, n / 2);
    inv += usingMergeSort(a + n / 2, n - n / 2);
    return inv + merge(a, n);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++) cin >> a[i];
        cout << "usingBIT :: " << usingBIT(a, n)
             << "\t usingMergeSort :: " << usingMergeSort(a, n) << endl;
    }
}
