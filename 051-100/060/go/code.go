// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #060, run
// TestSolution for test cases
package _060

// Solution for 060
func Solution(arr []int) (one, two []int, ok bool) {
	sum := 0
	for _, it := range arr {
		sum += it
	}
	if sum&1 == 1 {
		return // sum is odd i.e. 2 subsets not possible
	}
	sum >>= 1 // half sum == sum of one subset

	// Reference: solution 042
	lastSol := make([]bool, sum+1) // last solutions, n-1
	curSol := make([]bool, sum+1)  // current solutions, n
	lastUsed := make([]int, sum+1)
	for i := range lastUsed {
		lastUsed[i] = -1
	}
	lastSol[0] = true
	for i, ele := range arr {
		for s := 0; s <= sum; s++ {
			if s == 0 {
				curSol[s] = true
				continue
			}
			if ele <= s && lastSol[s-ele] {
				if lastUsed[s] == -1 {
					lastUsed[s] = i
				}
				curSol[s] = true
				continue
			}
			curSol[s] = lastSol[s]
		}
		curSol, lastSol = make([]bool, sum+1), curSol
	}
	if !lastSol[sum] {
		return // not possible
	}

	mp := map[int]struct{}{}
	in := lastUsed[sum]
	val := arr[in]
	for sum != 0 && sum-val != 0 {
		val = arr[in]
		mp[in] = struct{}{}
		one = append(one, val)
		sum -= arr[in]
		in = lastUsed[sum]
	}
	for i, ele := range arr {
		if _, ok := mp[i]; !ok {
			two = append(two, ele)
		}
	}
	ok = true
	return
}
