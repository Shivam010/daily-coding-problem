// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #066, run
// TestSolution for test cases
package _066

import (
	"math/rand"
	"time"
)

// CoinToss...
type CoinToss interface {
	// Toss...
	Toss() bool
}

// FairCoin: probability ratio: 50:50 (1:1) using BiasedCoin
type FairCoin struct {
	// C: biased over some thing (assuming unknown)
	C BiasedCoin
}

// Toss: for fair toss we need to reduce the probability to 50:50 (1:1)
// Let, probability ratio of FairCoin.C: BiasedCoin be 1:x (for 1:0)
// So, using two C coin tosses we can have 4 possibilities
// 0 0 | P => x*x
// 0 1 | P => x*(1-x)
// 1 0 | P => (1-x)*x
// 1 1 | P => (1-x)*(1-x)
// As we can see some equality in the middle two case, we can use them
// 0 1 -> implies 0
// 1 0 -> implies 1
// else -> recur Toss()
// => i.e. 1/4 + recur, 1/4 + recur (50:50)
// Reference solution to 045 problem
func (f FairCoin) Toss() bool {
	// Toss two biased coins to cancel out each others
	one, two := f.C.Toss(), f.C.Toss()
	if !one && two {
		return false
	}
	if one && !two {
		return true
	}
	return f.Toss()
}

// src: random numbers generator source
var src = rand.NewSource(time.Now().Unix())

// BiasedCoin with some probability, x over 0 if false and 1 if true
type BiasedCoin bool

// Biased Toss based on BiasedCoin value
func (c BiasedCoin) Toss() bool {
	// probability ratio: 1:3 <=> false:true
	res := src.Int63()&1 == 0
	res = res || src.Int63()&1 == 0
	if c {
		return res // biased over to 1 (true)
	}
	return !res // biased over to 0 (false)
}
