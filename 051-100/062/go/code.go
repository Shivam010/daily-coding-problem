// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #062, run
// TestSolution for test cases
package _062

// Solution for 062
// The solution matrix is:
//	70 35 15 5 1
//	35 20 10 4 1
//	15 10  6 3 1
//	 5  4  3 2 1
//	 1  1  1 1 1
// Answer for n*m = C(n+m-2)/C(n-1) = (n+m-2)!/((n-1)!*(m-1)!
func Solution(n, m int64) int64 {
	if n < m {
		n, m = m, n
	}
	if n == 1 || m == 1 {
		return 1
	}
	if n == 2 || m == 2 {
		if n > m {
			return n
		}
		return m
	}
	ans := int64(1)
	for i, j := n+m-2, m-1; i > n-1; i-- {
		ans *= i
		for j > 0 && ans%j == 0 {
			ans /= j
			j--
		}
	}
	return ans
}
