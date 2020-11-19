// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #009, run
// TestSolution for test cases
package _009

// Solution for 009
func Solution(in []int) int {
	n := len(in)
	if n == 0 {
		return 0
	}
	max := func(a, b int) int {
		if a > b {
			return a
		}
		return b
	}
	// answers: current, till last index, till last second index
	ans, lastAns, lastSecAns := 0, 0, 0
	for _, cur := range in {
		ans = max(max(lastAns, lastSecAns), max(cur, lastSecAns+cur))
		lastAns, lastSecAns = ans, lastAns
	}
	return ans
}
