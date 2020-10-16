/*
Daily Coding Challenge #044
---------------------------
This problem was asked by Google.

We can determine how "out of order" an array A is by counting the number of
inversions it has. Two elements `A[i]` and `A[j]` form an inversion if `A[i] >
A[j]` but `i < j`. That is, a smaller element appears after a larger element.

Given an array, count the number of inversions it has. Do this faster than
`O(N^2)` time.

You may assume each element in the array is distinct.

For example, a sorted list has zero inversions. The array `[2, 4, 1, 3, 5]` has
three inversions: `(2, 1)`, `(4, 1)`, and `(4, 3)`. The array `[5, 4, 3, 2, 1]`
has ten inversions: every distinct pair forms an inversion.

Run Using
---------
g++ 044/code.cpp -o bin/out && ./bin/out < 044/in.txt > 044/out.txt
*/
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
