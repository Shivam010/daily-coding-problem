// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge Other#001, run using
// g++ other/001/code.cpp -o bin/out
// ./bin/out < other/001/in.txt > other/001/out.txt
#include <bits/stdc++.h>
using namespace std;

/*
Solution Reference
------------------
For all `B(x)` will always be equal to `x` because:

Function `A(x)` is the euler's totient function, i.e. `A(x) = φ(x)`.
Therefore, `B(x)` is becomes sum of euler's totient function over all its
divisors, which is the number itself i.e.

`B(x) = x` and

`C(x)` is the sum of exponents of each prime in prime
factorization of `x`

https://proofwiki.org/wiki/Sum_of_Euler_Phi_Function_over_Divisors#:~:text=%E2%88%91d%E2%88%96n%20denotes,a%20number%20equals%20that%20number.
*/

int main() {
    int t;
    cin >> t;

    int input[t], mx = 0;
    for (int i = 0; i < t; i++) {
        // cin >> input[i];
        input[i] = i + 1;
        if (mx < input[i]) mx = input[i];
    }
    if (mx <= 3) mx = 4;

    vector<bool> composite(mx + 1, 0);
    vector<int> sumOfExponents(mx + 1, 0);

    int p = 2;
    sumOfExponents[2] = 1;
    for (int i = 4; i <= mx; i += 2) {
        composite[i] = true;
        int x = i;
        while (x % 2 == 0) {
            sumOfExponents[i]++;
            x /= 2;
        }
    }

    for (int i = 3; i <= mx; i += 2) {
        if (!composite[i]) {
            sumOfExponents[i] = 1;
            for (int in = i + i; in <= mx; in += i) {
                composite[in] = true;
                int x = in;
                while (x % i == 0) {
                    sumOfExponents[in]++;
                    x /= i;
                }
            }
        }
    }
    // cumulative summation of sumOfExponents for function `D`
    for (int i = 1; i <= mx; i++) sumOfExponents[i] += sumOfExponents[i - 1];
    for (int i = 0; i < t; i++) {
        cout << sumOfExponents[input[i]] << endl;
    }
    return 0;
}
