// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #042, run
// TestSolution for test cases
package _042

import "sort"

// Solution for 042
func Solution(arr []int, sum int) (out []int, ok bool) {
	sort.Ints(arr)
	out = make([]int, 0, len(arr))
	// solution(n, sum) is our solution, 'ok' for arr
	// 	=> solution(n, sum) = solution(n-1, sum) || solution(n-1, sum-arr(n))
	lastSol := make([]bool, sum+1) // last solutions, n-1
	curSol := make([]bool, sum+1)  // current solutions, n
	values := make([]int, sum+1)
	for i := range values {
		values[i] = -1
	}
	lastSol[0] = true
	for _, ele := range arr {
		for s := 0; s <= sum; s++ {
			// if s == 0, solution => true
			if s == 0 {
				curSol[s] = true
				continue
			}

			// if element is greater than s, use lastSol
			if ele > s {
				curSol[s] = lastSol[s]
				continue
			}

			// else, the 2 choices
			if lastSol[s-ele] { // use element
				if values[s] == -1 {
					values[s] = ele
				}
				curSol[s] = true
				continue
			} // or do not use it
			curSol[s] = lastSol[s]
		}
		curSol, lastSol = make([]bool, sum+1), curSol
	}
	if !lastSol[sum] {
		return out, ok
	}
	for sum != 0 && sum-values[sum] != 0 {
		out = append(out, values[sum])
		sum -= values[sum]
	}
	out = append(out, values[sum])
	return out, true
}
