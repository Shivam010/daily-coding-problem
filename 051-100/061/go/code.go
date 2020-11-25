// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #061, run
// TestSolution for test cases
package _061

// Solution for 061, returns x^y
func Solution(x, y int) int {
	ans := 1
	for y > 0 {
		if y&1 == 1 {
			ans *= x
		}
		y >>= 1
		x *= x
	}
	return ans
}
