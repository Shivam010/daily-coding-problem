// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _057

import (
	"reflect"
	"strconv"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		str  string
		k    int
		want []string
	}{
		{
			str:  "the quick brown fox jumps over the lazy dog",
			k:    10,
			want: []string{"the quick", "brown fox", "jumps over", "the lazy", "dog"},
		},
		{
			str:  "the quick brown fox jumps over the lazy dog",
			k:    3,
			want: nil,
		},
		{
			str:  "quick",
			k:    3,
			want: nil,
		},
		{
			str:  "quick",
			k:    10,
			want: []string{"quick"},
		},
		{
			str:  "the quick brown fox jumps over the lazy dog",
			k:    5,
			want: []string{"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"},
		},
	}
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			if got := Solution(tt.str, tt.k); !reflect.DeepEqual(got, tt.want) {
				t.Errorf("Solution() = %v, want %v", got, tt.want)
			}
		})
	}
}
