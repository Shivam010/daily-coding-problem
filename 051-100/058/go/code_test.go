// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _058

import (
	"reflect"
	"strconv"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		arr []int
		ele int
		ind int
	}{
		{
			arr: []int{13, 18, 25, 2, 8, 10},
			ele: 8,
			ind: 4,
		},
		{
			arr: []int{13, 18, 25, 2, 8, 10},
			ele: 13,
			ind: 0,
		},
		{
			arr: []int{13, 15, 18, 25, 2, 8, 10},
			ele: 18,
			ind: 2,
		},
		{
			arr: []int{1},
			ele: 1,
			ind: 0,
		},
		{
			arr: []int{1, 2, 3},
			ele: 2,
			ind: 1,
		},
	}
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if got := Search(tt.arr, tt.ele); !reflect.DeepEqual(got, tt.ind) {
				t.Errorf("Solution() = %v, want %v", got, tt.ind)
			}
		})
	}
}
