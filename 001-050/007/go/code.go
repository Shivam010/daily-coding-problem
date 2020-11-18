// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #007, run
// TestSolution for test cases
package _007

// Solution for 007
func Solution(msg string) uint64 {
	if len(msg) == 0 {
		return 0
	}
	// dp: maintains the solution for the string msg[:index]
	dp := make([]uint64, len(msg)+1)
	dp[0] = 1 // empty set
	for i := range msg {
		if msg[i] > '0' {
			dp[i+1] = dp[i]
		}
		if i > 0 && (msg[i-1] == '1' || (msg[i-1] == '2' && msg[i] < '7')) {
			dp[i+1] += dp[i-1]
		}
	}
	return dp[len(msg)]
}
