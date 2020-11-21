// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #011, run
// TestSolution for test cases
package _011

// Trie is the data structure that helps to implement autocomplete system
type Trie interface {
	// AddWords adds more words to the dictionary of Trie
	AddWords(words ...string)
	// Search will return list of words that can completed by
	// provided prefix, in the order they appeared in dictionary
	Search(prefix string) []string
	// Size of trie
	Size() int
}

// Add will add the word, which was
func NewTrie(words ...string) Trie {
	n := newNode()
	n.size = new(int)
	n.AddWords(words...)
	return n
}

// node: implements trie data structure
type node struct {
	next   map[rune]*node // next represent subsequent level of words
	isWord bool           // isWord marks the completion of a word
	size   *int           // size represents the size of the dictionary in the trie
}

func newNode() *node {
	return &node{next: map[rune]*node{}}
}

func (nd *node) Size() int {
	return *nd.size
}

func (nd *node) AddWords(words ...string) {
	for _, wd := range words {
		cur := nd
		for _, r := range wd {
			if _, ok := cur.next[r]; !ok {
				cur.next[r] = newNode()
			}
			cur = cur.next[r]
		}
		if !cur.isWord {
			*nd.size++
			cur.isWord = true
		} // else word was already present in trie
	}
}

func (nd *node) Search(prefix string) (out []string) {
	cur := nd
	for _, r := range prefix {
		if _, ok := cur.next[r]; !ok {
			return
		}
		cur = cur.next[r]
	}
	addWord := func(wd string) {
		out = append(out, wd)
	}
	cur.traverse(prefix, addWord)
	return out
}

func (nd *node) traverse(pre string, addWord func(string)) {
	if nd.isWord {
		addWord(pre)
	}
	for r, it := range nd.next {
		it.traverse(pre+string(r), addWord)
	}
}
