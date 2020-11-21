// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #045, run using
// g++ 001-050/045/c++/code.cpp -o bin/out
// ./bin/out < 001-050/045/c++/in.txt > 001-050/045/c++/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int rand5() {
    // will return random number between `1 and 5 (inclusive)` with uniform
    // probability of `1/5`
    return 1 + rand() % 5;
}

int rand7() {
    // As `7` if not one of the power of `5` hence it will not possible to
    // generate random number between `1 and 7` uniformly using `rand5()` in
    // finite time; and hence a different approach is to be considers:

    // `val` will have a random number between `1 and 25 (inclusive)` with
    // uniform probability of `1/25`
    int val = 5 * (rand5() - 1) + rand5();

    // if `val` is smaller than 22 i.e. between `1 and 21` we can directly
    // return the `number module 7` as our random number otherwise we again
    // recur for `rand7()`.
    //
    // Probability for `x` (`x` is in between `1 and 7`): `P(x)`
    // ```
    //  P(x) = (3/25) + (4/25)*(3/25) + (4/25)*(4/25)*(3/25) +
    //           (4/25)*(4/25)*(4/25)*(3/25) + ...... upto infinity
    //  i.e.
    //       = (3/25) / (1 - 4/25)
    //       = 1/7 (uniform)
    // ```

    if (val <= 21) return 1 + val % 7;
    // now, recur if greater than 21
    return rand7();
}

int main() {
    srand(time(NULL));
    int t;
    cin >> t;
    while (t--) {
        rand7();
    }
}
