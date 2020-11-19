// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #008, run
// TestSolution for test cases
package _008

// Node implements binary tree
type Node struct {
	value    int  // value of Node
	isUnival bool // is unival tree (having universal value)

	left, right *Node // left and right children

	count int // no. of unival subtrees in the node (including itself)
}

func NewNode(value int) *Node {
	return &Node{value: value}
}

func (n *Node) GetValue() int {
	return n.value
}

func (n *Node) AddChild(ch *Node) *Node {
	if n == nil {
		panic("nil node")
	}
	if n.left == nil {
		n.left = ch
		return ch
	}
	if n.right == nil {
		n.right = ch
		return ch
	}
	panic("binary tree node can only have two nodes")
}

// CountUnivals is solution for 008
func (n *Node) CountUnivals() int {
	if n == nil {
		return 0
	}
	if n.left == nil && n.right == nil {
		// leaf Node is unival
		n.isUnival = true
		return 1
	}
	n.count += n.left.CountUnivals()
	n.count += n.right.CountUnivals()
	if n.left != nil && n.right != nil &&
		n.left.isUnival && n.right.isUnival &&
		n.left.value == n.right.value && n.value == n.left.value {
		// n.value is universal value
		n.isUnival = true
		n.count++
	}
	return n.count
}
