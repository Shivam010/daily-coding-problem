// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _065

import (
	"reflect"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		mat [][]int
		out []int
	}{
		{
			mat: [][]int{
				{1, 2, 3, 4, 5},
				{6, 7, 8, 9, 10},
				{11, 12, 13, 14, 15},
				{16, 17, 18, 19, 20},
			},
			out: []int{
				1, 2, 3, 4, 5,
				10, 15, 20,
				19, 18, 17, 16,
				11, 6,
				7, 8, 9,
				14, 13, 12,
			},
		},
		{
			mat: [][]int{
				{1, 2, 3, 4, 5},
				{6, 7, 8, 9, 10},
			},
			out: []int{
				1, 2, 3, 4, 5,
				10, 9, 8, 7, 6,
			},
		},
		{
			mat: [][]int{
				{1, 2, 3},
				{8, 9, 4},
				{7, 6, 5},
			},
			out: []int{
				1, 2, 3,
				4, 5, 6,
				7, 8, 9,
			},
		},
		{
			mat: [][]int{{1}},
			out: []int{1},
		},
		{
			mat: [][]int{
				{1, 2},
				{2, 3},
			},
			out: []int{1, 2, 3, 2},
		},
	}
	for _, tt := range tests {
		t.Run("", func(t *testing.T) {
			if got := Solution(tt.mat); !reflect.DeepEqual(got, tt.out) {
				t.Errorf("Solution() = %v, want %v", got, tt.out)
			}
		})
	}
}
