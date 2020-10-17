/*
Daily Coding Challenge #045
---------------------------
This problem was asked by Two Sigma.

Using a function `rand5()` that returns an integer from `1 to 5 (inclusive)`
with uniform probability, implement a function `rand7()` that returns an integer
from `1 to 7 (inclusive)`.

Run Using
---------
g++ 045/code.cpp -o bin/out && ./bin/out < 045/in.txt > 045/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int rand5() {
    // will return random number between `1 and 5 (inclusive)` with uniform
    // probability of `1/5`
    return 1 + rand() % 5;
}

int rand7() {
    // as `7` if not one of the power of `5` hence it is not possible to
    // generate random number between `1 and 7` uniformally using `rand5()` in
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
