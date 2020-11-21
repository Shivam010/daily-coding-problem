// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #045, run
// TestSolution for test cases
package _045

import "math/rand"

// Rand5 will return random number between `1 and 5 (inclusive)`
// with uniform probability of `1/5`
func Rand5() int {
	return 1 + rand.Intn(5)
}

// Rand7 using Rand5...
// As `7` if not one of the power of `5`, hence it will not be possible to
// generate random number between `1 and 7` uniformly using Rand5 in finite
// time; and hence a different approach of infinite series is considered.
func Rand7() interface{} {
	// As using single Rand5() will only generate numbers b/w 1 to 5 which are
	// not enough for 7, hence we have to use two Rand5().
	// Therefore, val will have a random number between `1 and 25 (inclusive)`
	// with uniform probability of `1/25`
	val := 5*(Rand5()-1) + Rand5()

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
	// hence...
	if val <= 21 {
		return 1 + val%7
	}
	// now, recur if greater than 21
	return Rand7()
}
