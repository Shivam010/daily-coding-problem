// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #001, run
// TestSolution for test cases
package _001

// Solution for 001
func Solution(array []int, k int) bool {
	mp := map[int]struct{}{}
	for _, ele := range array {
		if _, ok := mp[ele]; ok {
			return true
		}
		mp[k-ele] = struct{}{}
	}
	return false
}
