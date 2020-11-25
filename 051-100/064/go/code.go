// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #064, run
// TestSolution for test cases
package _064

import (
	"sync"
	"sync/atomic"
)

func nextMoves(pos [2]int) [8][2]int {
	i, j := pos[0], pos[1]
	return [8][2]int{
		{i - 1, j - 2},
		{i - 1, j + 2},
		{i + 1, j - 2},
		{i + 1, j + 2},
		{i - 2, j - 1},
		{i - 2, j + 1},
		{i + 2, j - 1},
		{i + 2, j + 1},
	}
}

func valid(n int, pos [2]int) bool {
	i, j := pos[0], pos[1]
	if i < 0 || j < 0 {
		return false
	}
	if i >= n || j >= n {
		return false
	}
	return true
}

func backtrackCnt(n int, used int, pos [2]int, board [][]bool) int64 {
	if used >= n*n {
		return 1
	}
	cnt := int64(0)
	for _, next := range nextMoves(pos) {
		if !valid(n, next) {
			continue
		}
		ni, nj := next[0], next[1]
		if !board[ni][nj] {
			board[ni][nj] = true
			used++
			cnt += backtrackCnt(n, used, next, board)
			used--
			board[ni][nj] = false
		}
	}
	return cnt
}

// Solution for 064, # of knight's tour
func Solution(n int) int64 {

	solve := func(wg *sync.WaitGroup, i, j int, cnt *int64) {
		defer wg.Done()

		board := make([][]bool, n)
		for k := 0; k < n; k++ {
			board[k] = make([]bool, n)
		}
		board[i][j] = true
		used := 1
		atomic.AddInt64(cnt, backtrackCnt(n, used, [2]int{i, j}, board))
	}

	wg := &sync.WaitGroup{}
	half, single := int64(0), int64(0)
	for i := 0; i < n; i++ {
		wg.Add(1)
		go solve(wg, i, i, &single)
		for j := i + 1; j < n; j++ {
			wg.Add(1)
			go solve(wg, i, j, &half)
		}
	}
	wg.Wait()
	return half*2 + single
}
