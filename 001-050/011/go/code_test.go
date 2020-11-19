// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _011

import (
	"reflect"
	"sort"
	"strconv"
	"testing"
)

type unitCase struct {
	prefix   string
	response []string
}

func runTests(t *testing.T, trie Trie, tests []unitCase) {
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			got := trie.Search(tt.prefix)
			sort.Strings(got)
			if !reflect.DeepEqual(got, tt.response) {
				t.Errorf("trie.Search() = %v, want %v", got, tt.response)
			}
		})
	}
}

func TestTrie_SizeAndSearch(t *testing.T) {
	dict := []string{
		"deari", "deeli", "dog", "dear", "dearw", "deelw", "doge",
		"deare", "deele", "doga", "dogt", "deart", "deara", "doga",
		"dogy", "deary", "deely", "dogu", "dearu", "deelu", "world",
		"dogi", "deeld", "deelr", "deelo", "dogp", "deelt", "deel",
		"dearp", "deelp", "doga", "dogo", "dearo", "deela", "dears",
		"dogw", "deels", "dogd", "deard", "dream", "apple", "dogs",
		"deelt", "dear", "dogr", "dearr", "doga", "cream", "apple",
	}
	unique := 0
	mp := map[string]struct{}{}
	for _, wd := range dict {
		if _, ok := mp[wd]; !ok {
			unique++
			mp[wd] = struct{}{}
		}
	}
	trie := NewTrie(dict...)
	// size of dictionary == unique
	if got := trie.Size(); got != unique {
		t.Errorf("trie.Size() = %v, want %v", got, unique)
	}

	tests := []unitCase{
		{
			prefix: "de",
			response: []string{
				"dear", "deara", "deard", "deare", "deari", "dearo", "dearp",
				"dearr", "dears", "deart", "dearu", "dearw", "deary", "deel",
				"deela", "deeld", "deele", "deeli", "deelo", "deelp", "deelr",
				"deels", "deelt", "deelu", "deelw", "deely",
			},
		},
		{
			prefix: "dea",
			response: []string{
				"dear", "deara", "deard", "deare", "deari", "dearo", "dearp",
				"dearr", "dears", "deart", "dearu", "dearw", "deary",
			},
		},
		{
			prefix: "dee",
			response: []string{
				"deel", "deela", "deeld", "deele", "deeli", "deelo", "deelp",
				"deelr", "deels", "deelt", "deelu", "deelw", "deely",
			},
		},
		{
			prefix:   "a",
			response: []string{"apple"},
		},
		{
			prefix:   "did",
			response: nil,
		},
		{
			prefix:   "git",
			response: nil,
		},
	}
	runTests(t, trie, tests)
}

func TestTrie_AddWords(t *testing.T) {
	dict := []string{"aa", "dog", "mock"}
	trie := NewTrie(dict...)
	// run before adding more words
	runTests(t, trie, []unitCase{
		{
			prefix:   "a",
			response: []string{"aa"},
		},
		{
			prefix:   "og",
			response: nil,
		},
		{
			prefix:   "dog",
			response: []string{"dog"},
		},
		{
			prefix:   "mock",
			response: []string{"mock"},
		},
		{
			prefix:   "chock",
			response: nil,
		},
		{
			prefix:   "mockery",
			response: nil,
		},
	})

	// add more words
	trie.AddWords(
		"shock", "mockery", "mock",
		"ogy", "dog-cat", "shame", "kam",
		"apple", "shop", "mark",
	)

	// run after adding more words
	runTests(t, trie, []unitCase{
		{
			prefix:   "a",
			response: []string{"aa", "apple"},
		},
		{
			prefix:   "og",
			response: []string{"ogy"},
		},
		{
			prefix:   "dog",
			response: []string{"dog", "dog-cat"},
		},
		{
			prefix:   "mock",
			response: []string{"mock", "mockery"},
		},
		{
			prefix:   "chock",
			response: nil,
		},
		{
			prefix:   "mockery",
			response: []string{"mockery"},
		},
	})
}
