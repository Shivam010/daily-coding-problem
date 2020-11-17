// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _002

import (
	"reflect"
	"strconv"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		args []int64
		want []int64
	}{
		{
			args: []int64{},
			want: nil,
		},
		{
			args: []int64{1},
			want: nil,
		},
		{
			args: []int64{1, 2, 3, 4, 5},
			want: []int64{120, 60, 40, 30, 24},
		},
		{
			args: []int64{3, 2, 1},
			want: []int64{2, 3, 6},
		},
		{
			args: []int64{6, 5},
			want: []int64{5, 6},
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
