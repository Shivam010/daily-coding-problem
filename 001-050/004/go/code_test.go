// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _004

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
			args: []int{3, 4, -1, 1},
			want: 2,
		},
		{
			args: []int{1, 2, 0},
			want: 3,
		},
		{
			args: []int{1, -1, 9992349},
			want: 2,
		},
		{
			args: []int{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10},
			want: 1,
		},
		{
			args: []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
			want: 11,
		},
		{
			args: []int{-2, -1, 0, 1, 1},
			want: 2,
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
