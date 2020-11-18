// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #005, run
// TestSolution for test cases
package _005

type Pair struct{ a, b interface{} }

// Cons constructs a pair
func Cons(a, b interface{}) Pair {
	return Pair{a: a, b: b}
}

// Car returns the first element of that Pair
func Car(p Pair) interface{} {
	return p.a
}

// Cdr returns the last element of that Pair
func Cdr(p Pair) interface{} {
	return p.b
}
