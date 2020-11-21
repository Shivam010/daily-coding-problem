// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #052, run
// TestSolution for test cases
package _052

import "sync"

// CacheKey represent type of the key to be used in Cache,
// for the convenience of changing it in future, e.g. to string
type CacheKey int

// LRUCache provides the interface for the LRU (Least Recently
// Used) caching system.
type LRUCache interface {
	// Set will set the provided key to the value and will remove
	// the least recently used node, if size is reached
	Set(key CacheKey, value interface{})
	// Get will return the stored value for the provided key and
	// a true status, if found, other nil and false
	Get(key CacheKey) (interface{}, bool)
}

const sizeGreaterThanZero = "NewLRUCache requires size greater than zero"

// NewLRUCache returns a sized LRU cache implementation (LRUCache)
// It requires size greater than zero, otherwise it will panic.
func NewLRUCache(size int) LRUCache {
	if size <= 0 {
		panic(sizeGreaterThanZero)
	}
	l := &lru{
		mu:     sync.Mutex{},
		size:   size,
		data:   make(map[CacheKey]*node, size+1), // +1 for buffer during set
		header: new(node),
		footer: new(node),
	}
	l.header.next = l.footer
	l.footer.prev = l.header
	return l
}

// lru: implements LRUCache interface
type lru struct {
	mu sync.Mutex // guards lru

	size int                // cache size limit
	data map[CacheKey]*node // map for key to node value

	// header is the starting head of the LRU
	// header will have least recently used node in its next.
	header *node
	// footer is the end part or tail of the LRU
	// footer will have most recently used node in its prev.
	footer *node
}

func (l *lru) Set(key CacheKey, value interface{}) {
	l.mu.Lock()
	defer l.mu.Unlock()

	if val, ok := l.data[key]; ok {
		// previous set value should be detached because,
		// now, it is most recently used hence, will be
		// reattached to the footer using l.addNode
		l.detach(val)
	}
	// set new key & value
	l.data[key] = l.addNode(key, value)

	// if cache is full, i.e. size limit is reached, remove
	// a least recently used entry, from header side
	if l.size < len(l.data) {
		lastKey := l.header.next.key
		l.detach(l.header.next) // detach from list
		delete(l.data, lastKey) // delete from map
	}
}

func (l *lru) Get(key CacheKey) (interface{}, bool) {
	l.mu.Lock()
	defer l.mu.Unlock()

	val, ok := l.data[key]
	if !ok {
		return nil, false // key: not found
	}

	// key: found, hence it should be marked as most recently used
	// and should be moved near footer
	l.detach(val)     // detach it
	l.nearFooter(val) // attach it to footer
	return val.value, true
}

// addNode will add a new node with the provided inputs and returns it
// the new node will be added in the footer side as most recently used
func (l *lru) addNode(key CacheKey, value interface{}) *node {
	n := new(node)
	n.key, n.value = key, value
	l.nearFooter(n) // mark as most recently used
	return n
}

// nearFooter will mark a node as the most recently used
// by marking it previous to footer
func (l *lru) nearFooter(n *node) {
	n.next, n.prev = l.footer, l.footer.prev
	n.prev.next, n.next.prev = n, n
}

// detach will remove the current node, n from the cache list
func (l *lru) detach(n *node) {
	n.prev.next = n.next
	n.next.prev = n.prev
	n.prev, n.next = nil, nil
}

// node is the individual `value` item that will contain actual
// cache value, and it makes the linked list of max size lru.size
type node struct {
	key   CacheKey
	value interface{}

	prev *node // prev -> points to the previous node in list
	next *node // next -> points to the next node in list
}
