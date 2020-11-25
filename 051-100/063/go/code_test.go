// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _063

import (
	"reflect"
	"testing"
)

func TestSolution(t *testing.T) {
	type query struct {
		word string
		resp bool
	}
	tests := []struct {
		mat     [][]rune
		queries []query
	}{
		{
			mat: [][]rune{
				{'F', 'A', 'C', 'I'},
				{'O', 'B', 'Q', 'P'},
				{'A', 'N', 'O', 'B'},
				{'M', 'A', 'S', 'S'},
			},
			queries: []query{
				{word: "FOAM", resp: true},
				{word: "ABNC", resp: false},
				{word: "MASS", resp: true},
				{word: "MNQI", resp: false},
				{word: "FBOS", resp: false},
				{word: "ANOB", resp: true},
			},
		},
		{
			mat: [][]rune{
				{'a', 'd', 'f'},
				{'b', 'c', 'e'},
				{'c', 's', 'm'},
			},
			queries: []query{
				{word: "abc", resp: true},
				{word: "abcd", resp: false},
				{word: "bce", resp: true},
				{word: "fcd", resp: false},
				{word: "bde", resp: false},
				{word: "fem", resp: true},
			},
		},
	}
	for _, tt := range tests {
		t.Run("", func(t *testing.T) {
			fn := SolutionFunc(tt.mat)
			for _, que := range tt.queries {
				t.Run(que.word, func(t *testing.T) {
					if got := fn(que.word); !reflect.DeepEqual(got, que.resp) {
						t.Errorf("SolutionFunc()() = %v, want %v", got, que.resp)
					}
				})
			}
		})
	}
}
