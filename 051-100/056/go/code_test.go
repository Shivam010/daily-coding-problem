// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _056

import (
	"fmt"
	"reflect"
	"testing"
)

func TestSolution(t *testing.T) {
	yes := struct{}{}
	tests := []struct {
		ks   []int
		gr   Graph
		chrN int // chromatic number
	}{
		{
			ks:   []int{0, 1, 2, 3},
			gr:   Graph{},
			chrN: 0,
		},
		{
			ks: []int{0, 1, 2, 3},
			gr: Graph{
				0: {1: yes, 2: yes, 3: yes},
				1: {0: yes},
				2: {0: yes},
				3: {0: yes},
			},
			chrN: 2,
		},
		{
			ks: []int{4, 0, 1, 2, 3},
			gr: Graph{
				1: {0: yes, 2: yes},
				2: {0: yes, 1: yes},
				0: {1: yes, 2: yes},
			},
			chrN: 3,
		},
		{
			ks: []int{4, 0, 1, 2, 3},
			gr: Graph{
				1: {0: yes},
				2: {0: yes, 3: yes},
				0: {1: yes, 2: yes},
				3: {2: yes},
			},
			chrN: 2,
		},
		{
			ks: []int{4, 0, 1, 2, 3},
			gr: Graph{
				1: {0: yes, 2: yes},
				2: {0: yes, 3: yes, 1: yes},
				0: {1: yes, 2: yes},
				3: {2: yes},
			},
			chrN: 3,
		},
		{
			ks: []int{4, 0, 1, 2, 3},
			gr: Graph{
				1: {0: yes, 3: yes},
				2: {0: yes, 3: yes},
				0: {1: yes, 2: yes},
				3: {1: yes, 2: yes},
			},
			chrN: 2,
		},
		{
			ks: []int{4, 0, 1, 2, 3},
			gr: Graph{
				1: {0: yes, 3: yes},
				2: {0: yes, 3: yes},
				0: {1: yes, 2: yes},
				3: {1: yes, 2: yes, 0: yes},
			},
			chrN: 3,
		},
	}
	const tmp = "graph=%v k= %v"
	for i, tt := range tests {
		for _, k := range tt.ks {
			t.Run(fmt.Sprintf(tmp, i, k), func(t *testing.T) {
				if got, want := Solution(tt.gr, k), k >= tt.chrN; !reflect.DeepEqual(got, want) {
					t.Errorf("Solution() = %v, want %v", got, want)
				}
			})
		}
	}
}
