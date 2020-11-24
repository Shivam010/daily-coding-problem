// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #058, run
// TestSolution for test cases
package _058

// Search solution for 058, returns index of ele if found or -1
func Search(arr []int, ele int) int {
	ln := len(arr) - 1
	if ln == -1 {
		return -1
	}
	if ln == 0 {
		if arr[0] == ele {
			return 0
		}
		return -1
	}
	mid := 1+ln / 2
	if ele == arr[mid] {
		return mid
	}
	if arr[0] < arr[ln] {
		if ele < arr[mid] {
			return Search(arr[:mid], ele)
		}
		return mid + Search(arr[mid:], ele)
	}
	ans := Search(arr[:mid], ele)
	if ans == -1 {
		ans = mid + Search(arr[mid:], ele)
	}
	return ans
}
