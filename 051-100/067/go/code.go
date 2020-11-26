// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #067, run
// TestSolution for test cases
package _067

import (
	"sync"
)

// CacheKey represent type of the key to be used in Cache,
// for the convenience of changing it in future, e.g. to string
type CacheKey int

// LFUCache provides the interface for the LFU (Least Frequently
// Used) caching system.
type LFUCache interface {
	// Set will set the provided key to the value and will remove
	// the least frequently used node, if size is reached
	Set(key CacheKey, value interface{})
	// Get will return the stored value for the provided key and
	// a true status, if found, other nil and false
	Get(key CacheKey) (interface{}, bool)
}

const sizeGreaterThanZero = "NewLFUCache requires size greater than zero"

// NewLFUCache returns a sized LFU cache implementation (LFUCache)
// It requires size greater than zero, otherwise it will panic.
func NewLFUCache(size int) LFUCache {
	if size <= 0 {
		panic(sizeGreaterThanZero)
	}
	l := &lfu{
		mu:     sync.Mutex{},
		size:   size,
		data:   make(map[CacheKey]*node, size+1), // +1 for buffer during set
		header: newFreqNode(0),
	}
	l.header.header = nil
	l.header.footer = nil
	return l
}

// lfu: implements LFUCache interface
type lfu struct {
	mu sync.Mutex // guards lfu

	size int                // cache size limit
	data map[CacheKey]*node // map for key to node value

	// header: is the starting head of the frequency lists
	// header will have lowest count frequency in it's next
	header *freqNode
}

func (l *lfu) Set(key CacheKey, value interface{}) {
	l.mu.Lock()
	defer l.mu.Unlock()

	// check the key
	val, ok := l.data[key]

	// if cache is full, i.e. size limit is reached, remove
	// a least frequently used entry, from head freqNode
	if !ok && l.size == len(l.data) {
		least := l.header.next // least frequent node
		lastKey := least.header.next.key

		l.detachNode(least.header.next) // detach from list
		delete(l.data, lastKey)         // delete from map

		// check if preFreq list is empty, if so delete it
		if least != l.header && least.header.next == least.footer {
			l.detachFreqNode(least)
		}
	}

	// preFreq: initial(or present state) occurrence count, freqNode
	preFreq := l.header
	if ok {
		// previous set value should be detached because,
		// now, it frequency of occurrence is increased
		preFreq = val.freq
		l.detachNode(val)
	}
	// set new key & value
	l.data[key] = l.addNode(preFreq, key, value)
}

func (l *lfu) Get(key CacheKey) (interface{}, bool) {
	l.mu.Lock()
	defer l.mu.Unlock()

	val, ok := l.data[key]
	if !ok {
		return nil, false // key: not found
	}
	// key: found, hence it should be marked as most frequently used
	// and should be moved near footer
	l.detachNode(val)        // detach it
	l.increaseFrequency(val) // attach it to next freqNode
	return val.value, true
}

// addNode will add a new node with the provided input, key & value in the
// freqNode immediately after preFreq, and returns the new node.
// The new node will be added in the footer side of freqNode as most recently used
func (l *lfu) addNode(preFreq *freqNode, key CacheKey, value interface{}) *node {
	n := new(node)
	n.key, n.value = key, value
	n.freq = preFreq
	l.increaseFrequency(n) // increase frequency of node
	return n
}

// increaseFrequency will increase a frequency of node and add it to next
// freqNode as the most recently used node in it's list
func (l *lfu) increaseFrequency(n *node) {
	preFreq := n.freq
	n.freq = l.nextFreq(preFreq)
	n.next, n.prev = n.freq.footer, n.freq.footer.prev
	n.prev.next, n.next.prev = n, n
	// check if preFreq list is empty, if so delete it
	if preFreq != l.header && preFreq.header.next == preFreq.footer {
		l.detachFreqNode(preFreq)
	}
}

// nextFreq returns the next freqNode after fn, having frequency one greater
// than that of fn, if not exist, it will create new
func (l *lfu) nextFreq(fn *freqNode) *freqNode {
	next := fn.next
	if next != nil && next.frequency == fn.frequency+1 {
		// found
		return next
	}
	// not found, create new freqNode
	cur := newFreqNode(fn.frequency + 1)
	cur.next, cur.prev = next, fn
	// update the existing node's pointers
	fn.next = cur
	if next != nil {
		next.prev = cur
	}
	return cur
}

// detachNode will remove the current node, n from the frequency list
// Note that it does not remove the pointer to it's freqNode for future
// references in other methods
func (l *lfu) detachNode(n *node) {
	// remove from list
	n.prev.next = n.next
	n.next.prev = n.prev
	n.prev, n.next = nil, nil
	// Note: n.freq should not be reset, for future references
}

// detachFreqNode will remove the current freqNode, fn from it's list
func (l *lfu) detachFreqNode(fn *freqNode) {
	fn.prev.next = fn.next
	if fn.next != nil { // as freqNode list does not have a footer freqNode
		fn.next.prev = fn.prev
	}
	fn.prev, fn.next = nil, nil
}

// freqNode is the frequency node containing the list of node(s)
// having same occurrence count
type freqNode struct {
	// frequency is occurrence count of these nodes
	frequency int

	// occurrence count list pointers
	prev *freqNode // prev -> points to the previous freqNode in list
	next *freqNode // next -> points to the next freqNode in list

	// header is the starting head of the node list
	// header will have least recently used node in its next.
	header *node
	// footer is the end part or tail of the LFU
	// footer will have most recently used node in its prev.
	footer *node
}

// newFreqNode returns a new freqNode with provided frequency count
func newFreqNode(cnt int) *freqNode {
	n := new(freqNode)
	n.frequency = cnt
	n.header = new(node)
	n.footer = new(node)
	n.header.next = n.footer
	n.footer.prev = n.header
	return n
}

// node is the individual `value` item that will contain actual
// cache value, and it makes the linked list of max size lfu.size
type node struct {
	key   CacheKey
	value interface{}

	// freq points to the node's freqNode
	freq *freqNode

	prev *node // prev -> points to the previous node in list
	next *node // next -> points to the next node in list
}
