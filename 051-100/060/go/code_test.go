// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _060

import (
	"reflect"
	"sort"
	"testing"
)

func TestSolution(t *testing.T) {
	type want struct {
		one []int
		two []int
		ok  bool
	}
	tests := []struct {
		arr  []int
		want want
	}{
		{
			arr: []int{15, 5, 10, 15, 10, 35, 20},
			want: want{
				one: []int{5, 10, 10, 15, 15},
				two: []int{20, 35},
				ok:  true,
			},
		},
		{
			arr: []int{15, 5, 20, 10, 35, 15, 10},
			want: want{
				one: []int{10, 10, 15, 20},
				two: []int{5, 15, 35},
				ok:  true,
			},
		},
		{
			arr: []int{15, 5, 20, 10, 35},
			want: want{
				one: nil,
				two: nil,
				ok:  false,
			},
		},
		{
			arr: []int{15, 5},
			want: want{
				one: nil,
				two: nil,
				ok:  false,
			},
		},
		{
			arr: []int{15, 5, 20, 10, 35, 35},
			want: want{
				one: []int{5, 20, 35},
				two: []int{10, 15, 35},
				ok:  true,
			},
		},
	}
	for _, tt := range tests {
		t.Run("", func(t *testing.T) {
			one, two, ok := Solution(tt.arr)
			sort.Ints(one)
			sort.Ints(two)
			if len(one) < len(two) {
				one, two = two, one
			}
			if !reflect.DeepEqual(one, tt.want.one) {
				t.Errorf("Solution().one = %v, want %v", one, tt.want.one)
			}
			if !reflect.DeepEqual(two, tt.want.two) {
				t.Errorf("Solution().two = %v, want %v", two, tt.want.two)
			}
			if !reflect.DeepEqual(ok, tt.want.ok) {
				t.Errorf("Solution().ok = %v, want %v", ok, tt.want.ok)
			}
		})
	}
}
