// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _007

import (
	"reflect"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		msg  string
		want uint64
	}{
		{
			msg:  "111",
			want: 3,
		},
		{
			msg:  "100",
			want: 0,
		},
		{
			msg:  "4",
			want: 1,
		},
		{
			msg:  "675417635611",
			want: 4,
		},
		{
			msg:  "363421201",
			want: 2,
		},
		{
			msg:  "2011",
			want: 2,
		},
		{
			msg:  "110",
			want: 1,
		},
		{
			msg:  "98545620",
			want: 1,
		},
		{
			msg:  "1056219",
			want: 3,
		},
		{
			msg:  "123421",
			want: 6,
		},
		{
			msg:  "01234",
			want: 0,
		},
		{
			msg:  "201",
			want: 1,
		},
		{
			msg:  "203410",
			want: 1,
		},
		{
			msg:  "98545630",
			want: 0,
		},
		{
			msg:  "4333433341233341201120112011233343120112011201334333433343334333433343334333433343334333341201123343334333334120112343120112011233433343334333433343334333433343334333433343334333433343334333433343334333433320334333433343334333433343334333433343",
			want: 120000,
		},
	}
	for _, tt := range tests {
		t.Run(tt.msg, func(t *testing.T) {
			if got := Solution(tt.msg); !reflect.DeepEqual(got, tt.want) {
				t.Errorf("Solution(...) = %v, want %v", got, tt.want)
			}
		})
	}
}
