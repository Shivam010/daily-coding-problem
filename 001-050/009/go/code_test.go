// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _009

import (
	"reflect"
	"strconv"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		args []int
		want int
	}{
		{
			args: []int{2, 4, 6, 2, 5},
			want: 13,
		},
		{
			args: []int{5, 1, 1, 5},
			want: 10,
		},
		{
			args: []int{-5, -1, -1, -5},
			want: 0,
		},
		{
			args: []int{5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5, 5, 5, 10, 100, 10, 5},
			want: 1100,
		},
		{
			args: []int{-2, -4, -6, -2, -5},
			want: 0,
		},
		{
			args: []int{-2, -4, -6, -1, -5},
			want: 0,
		},
		{
			args: []int{-2, -4, -6, -1, 5},
			want: 5,
		},
		{
			args: []int{1},
			want: 1,
		},
		{
			args: []int{1, 2},
			want: 2,
		},
		{
			args: []int{-1},
			want: 0,
		},
	}
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if got := Solution(tt.args); !reflect.DeepEqual(got, tt.want) {
				t.Errorf("Solution() = %v, want %v", got, tt.want)
			}
		})
	}
}
