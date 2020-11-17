// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #004, run
// TestSolution for test cases
package _004

// Solution for 004
func Solution(in []int) int {
	n := len(in)
	// modify `in` => all negative values are in end
	for i := 0; i < n; {
		if in[i] <= 0 {
			n--
			in[i], in[n] = in[n], in[i]
			continue
		}
		i++
	}
	if n == 0 {
		return 1
	}
	// all elements in `in` till n are positive
	for i := 0; i < n; i++ {
		// mark position in array(0,n) negative if value is smaller than n
		pos := in[i]
		if pos < 0 {
			pos = -pos
		}
		if pos <= n && in[pos-1] > 0 { // not already marked
			in[pos-1] = -in[pos-1]
		}
	}
	// now, position of first unmarked element will be our answer
	for i := 0; i < n; i++ {
		if in[i] > 0 {
			return i + 1
		}
	}
	return n + 1
}
