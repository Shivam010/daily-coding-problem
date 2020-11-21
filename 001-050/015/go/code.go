// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #015, run
// TestSolution for test cases
package _015

import (
	"math/rand"
	"time"
)

// UniformSelection: Selecting a random element uniformly from a stream is
// tedious task, we can not store all the elements to be randomly selected.
// Instead, if we maintain the total number of elements received, so far, we
// can use infinite series to obtain a uniform probability.
func UniformSelection(stream <-chan interface{}) <-chan interface{} {
	out := make(chan interface{})
	src := rand.NewSource(time.Now().Unix()) // random source
	total := int64(0)
	last := interface{}(nil) // last selected element
	go func() {
		for ele := range stream {
			total++

			// if ele is the first element: uniform probability of selection
			// will 1 and hence, it should be selected
			// Now, for next elements, we select using a random number, among
			// total elements so far streamed (rn)
			rn := 1 + src.Int63()%total

			// if rn is total number of elements, select it. Hence, probability
			// P(ele) = 1/total => uniform
			if total == 1 || rn == total {
				last = ele // and save it for latter use
			} // else previous one should be used.

			out <- last // out-stream selected number

			// Proof: Probability = 1/total
			// Probability for last element to be selected.
			//	=> P(last) = 1/total
			// Now, Probability for 2nd last element will be: should be selected
			// at previous chance (1/(total-1)) and then, previous one should be
			// selected again so ((total-1)/total).
			//	=> P(last-1) = 1/(total-1)*((total-1)/total)
			// 	=> P(last-1) = 1/total
			// Similarly,
			//	=> P(last-2) = 1/(total-2)*((total-2)/(total-1))*((total-1)/total)
			// 	=> P(last-2) = 1/total, uniform
		}
	}()
	return out
}
