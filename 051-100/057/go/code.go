// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #057, run
// TestSolution for test cases
package _057

// Solution for 057
func Solution(str string, k int) []string {
	ln := len(str)
	if ln <= k { // base case
		return []string{str}
	}

	out := make([]string, 0, 1+ln/k)
	lastW, lastIn := "", 0
	out = append(out, lastW)

	// adding a space in end so that last element will be automatically procesed
	str += " "

	for i := range str {
		if str[i] == ' ' {
			ln := len(lastW)
			if ln > k {
				return nil // solution not possible
			}
			ln = len(out[lastIn]) + 1 + ln
			if ln <= k {
				if out[lastIn] != "" {
					out[lastIn] += " "
				}
				out[lastIn] += lastW
				lastW = ""
			}
			if ln >= k {
				lastIn++
				out = append(out, lastW)
			}
			lastW = ""
			continue
		}
		lastW += string(str[i])
	}

	return out
}
