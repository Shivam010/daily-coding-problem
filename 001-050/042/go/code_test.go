// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _042

import (
	"reflect"
	"strconv"
	"testing"
)

func TestSolution(t *testing.T) {
	type args struct {
		arr []int
		sum int
	}
	type want struct {
		ok  bool
		out []int
	}
	tests := []struct {
		args args
		want want
	}{
		{
			args: args{
				arr: []int{12, 1, 61, 5, 9, 2},
				sum: 24,
			},
			want: want{ok: true, out: []int{12, 9, 2, 1}},
		},
		{
			args: args{
				arr: []int{1, 2, 3, 5, 6},
				sum: 12,
			},
			want: want{ok: true, out: []int{6, 5, 1}},
		},
		{
			args: args{
				arr: []int{12, 12, 21, 21, 12, 12},
				sum: 108,
			},
			want: want{ok: false, out: []int{}},
		},
		{
			args: args{
				arr: []int{21, 12, 21, 20, 12, 34},
				sum: 108,
			},
			want: want{ok: true, out: []int{34, 21, 21, 20, 12}},
		},
		{
			args: args{
				arr: []int{70, 100, 20, 30, 40, 9, 100, 1},
				sum: 109,
			},
			want: want{ok: true, out: []int{100, 9}},
		},
		{
			args: args{
				arr: []int{12, 12, 21, 21, 12, 12, 12, 12, 21, 21, 12, 12},
				sum: 2000,
			},
			want: want{ok: false, out: []int{}},
		},
		{
			args: args{
				arr: []int{12, 12, 21, 21, 12, 12, 12, 12, 21, 21, 12, 12, 12},
				sum: 2000,
			},
			want: want{ok: false, out: []int{}},
		},
		{
			args: args{
				arr: []int{12, 12, 21, 21, 12, 12, 12, 12, 21, 21, 12, 12, 12, 12},
				sum: 2000,
			},
			want: want{ok: false, out: []int{}},
		},
		{
			args: args{
				arr: []int{12, 12, 21, 21, 12, 12, 12, 12, 21, 21, 12, 12, 12, 12, 12},
				sum: 0,
			},
			want: want{ok: true, out: []int{}},
		},
		{
			args: args{
				arr: []int{12, 12, 21, 21, 12, 12, 12, 12, 21, 21, 12, 12, 12, 12, 12, 12},
				sum: 195,
			},
			want: want{ok: true, out: []int{21, 21, 21, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12}},
		},
	}
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if out, ok := Solution(tt.args.arr, tt.args.sum);
				ok != tt.want.ok && !reflect.DeepEqual(out, tt.want.out) {
				t.Log("Args", tt.args)
				t.Errorf("Solution() = %v-%v, want %v-%v", out, ok, tt.want.out, tt.want.ok)
			}
		})
	}
}
