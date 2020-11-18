// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #006, run
// TestSolution for test cases
package _006

import (
	"fmt"
	"io"
	"unsafe"
)

// XORLinkedList: the XOR linked list interface
type XORLinkedList interface {
	// Add adds the element value to the end
	Add(val int)
	// Get returns the node at index and true, if found
	Get(in int) (int, bool)
	// Print prints the complete list in writer `w`
	Print(w io.Writer)
}

func NewXorLinkedList() XORLinkedList {
	return &node{isEmpty: true}
}

type node struct {
	value int
	both  *node

	// isEmpty: is used as value can be zero too
	isEmpty bool
}

// xor: though it is unsafe, as GC uses pointers
func xor(a, b *node) *node {
	pa := unsafe.Pointer(a)
	pb := unsafe.Pointer(b)
	return (*node)(unsafe.Pointer(uintptr(pa) ^ uintptr(pb)))
}

func (n *node) Add(val int) {
	if n == nil {
		return
	}
	if n.isEmpty {
		n.value = val
		n.isEmpty = false
		return
	}
	// new element
	nw := &node{value: val}

	var last *node
	cur := n
	for cur.both != nil {
		next := xor(cur.both, last)
		last = cur
		cur = next
	}
	cur.both = xor(last, nw)
}

func (n *node) Get(in int) (int, bool) {
	if n == nil || n.isEmpty {
		return 0, false
	}
	var last *node
	cur := n
	for in > 0 && cur.both != nil {
		in--
		next := xor(cur.both, last)
		last = cur
		cur = next
	}
	if in > 0 {
		return 0, false
	}
	return cur.value, true
}

func (n *node) Print(w io.Writer) {
	val, ok := n.Get(0)
	for in := 1; ok; in++ {
		_, _ = fmt.Fprintf(w, "%v ", val)
		val, ok = n.Get(in)
	}
}
