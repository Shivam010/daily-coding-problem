// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #002, run
// TestSolution for test cases
package _002

// Solution for 002
func Solution(in []int64) (out []int64) {
	n := len(in)
	if n <= 1 {
		return
	}
	left := make([]int64, n)
	right := make([]int64, n)

	left[0] = in[0]
	for i := 1; i < n; i++ {
		left[i] = left[i-1] * in[i]
	}

	right[n-1] = in[n-1]
	for i := n - 2; i > -1; i-- {
		right[i] = right[i+1] * in[i]
	}

	out = make([]int64, n)
	out[0], out[n-1] = right[1], left[n-2]
	for i := 1; i < n-1; i++ {
		out[i] = left[i-1] * right[i+1]
	}
	return
}
