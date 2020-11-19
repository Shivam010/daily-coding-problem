// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _008

import (
	"reflect"
	"strconv"
	"testing"
)

func buildTree(values []int, edges map[int][]int) *Node {
	if len(values) < 1 {
		panic("root => 1")
	}
	root := NewNode(values[1])

	nodeMp := map[int]*Node{1: root}
	newNode := func(val int) *Node {
		kn, ok := nodeMp[val]
		if !ok {
			kn = NewNode(values[val])
			nodeMp[val] = kn
		}
		return kn
	}

	for key, list := range edges {
		kn := newNode(key)
		if len(list) >= 1 {
			kn.AddChild(newNode(list[0]))
		}
		if len(list) >= 2 {
			kn.AddChild(newNode(list[1]))
		}
	}
	return root
}

func TestOne(t *testing.T) {
	tests := []struct {
		values      []int
		edges       map[int][]int
		noOfUnivals int
	}{
		{
			values: []int{-1, 0, 1, 0, 1, 0, 1, 1},
			edges: map[int][]int{
				1: {2, 3},
				3: {4, 5},
				4: {6, 7},
			},
			noOfUnivals: 5,
		},
		{
			values: []int{-1, 0, 1},
			edges: map[int][]int{
				1: {2},
			},
			noOfUnivals: 1,
		},
	}
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			tree := buildTree(tt.values, tt.edges)
			if got := tree.CountUnivals(); !reflect.DeepEqual(got, tt.noOfUnivals) {
				t.Errorf("tree.CountUnivals() = %v, want %v", got, tt.noOfUnivals)
			}
		})
	}
}
