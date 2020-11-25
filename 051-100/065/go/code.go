// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #065, run
// TestSolution for test cases
package _065

type limits struct {
	lower, upper int
}

// Solution for 065
func Solution(mat [][]int) []int {
	if len(mat) == 0 {
		return nil
	}
	for i := range mat {
		if len(mat[i]) != len(mat[0]) {
			panic("matrix is invalid")
		}
	}

	n, m := len(mat), len(mat[0])
	rowL := limits{lower: 0, upper: n - 1}
	colL := limits{lower: 0, upper: m - 1}

	i, j, delta := 0, 0, 1
	out := make([]int, 0, n*m)

	for k := 0; k < n*m; k++ {
		out = append(out, mat[i][j])
		if colL.lower <= j+delta && j+delta <= colL.upper {
			j += delta
		} else if rowL.lower <= i+delta && i+delta <= rowL.upper {
			i += delta
		} else {
			if delta == 1 {
				delta = -1
				rowL.lower++
				colL.upper--
			} else {
				delta = 1
				colL.lower++
				rowL.upper--
			}
			if colL.lower <= j+delta && j+delta <= colL.upper {
				j += delta
			} else if rowL.lower <= i+delta && i+delta <= rowL.upper {
				i += delta
			}
		}
	}

	return out
}
