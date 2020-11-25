// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #063, run
// TestSolution for test cases
package _063

import "strings"

type FindWord func(word string) bool

// Solution for 063, assuming all rows have smae length
func SolutionFunc(mat [][]rune) FindWord {
	if len(mat) == 0 || len(mat[0]) == 0 {
		return func(word string) bool { return false }
	}
	allPossibles := map[string]struct{}{}
	for i := range mat {
		if len(mat[i]) != len(mat[0]) {
			panic("row lengths must be same")
		}
		one := strings.Builder{}
		for j := range mat[i] {
			one.WriteRune(mat[i][j])
		}
		allPossibles[one.String()] = struct{}{}
	}
	for j := range mat[0] {
		one := strings.Builder{}
		for i := range mat {
			one.WriteRune(mat[i][j])
		}
		allPossibles[one.String()] = struct{}{}
	}
	return func(word string) bool {
		_, ok := allPossibles[word]
		return ok
	}
}
