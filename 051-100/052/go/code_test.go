// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _052

import (
	"strconv"
	"sync"
	"testing"
)

func TestCache(t *testing.T) {
	lru := NewLRUCache(20)
	for i := 0; i < 10; i++ {
		lru.Set(CacheKey(i), i)
	}
	for i := 10; i < 20; i++ {
		lru.Set(CacheKey(i), strconv.Itoa(i))
	}
	for i := 0; i < 30; i++ {
		val, ok := lru.Get(CacheKey(i))
		if i < 20 {
			if !ok {
				t.Errorf("LRU: %v must be cached, got %v", i, ok)
			}
			if val == nil {
				t.Errorf("LRU: %v must be cached, got nil-true", i)
			}
		}
		if i < 10 {
			in, ok := val.(int)
			if !ok || in != i {
				t.Errorf("LRU: int(%v) must be returned, got %v of type:%T", i, in, in)
			}
		}
		if i >= 10 && i < 20 {
			in, ok := val.(string)
			if !ok || in != strconv.Itoa(i) {
				t.Errorf("LRU: string(%v) must be returned, got %v of type:%T", i, in, in)
			}
		}
		if i >= 20 {
			if ok {
				t.Errorf("LRU: %v must not be cached, got %v", i, ok)
			}
			if val != nil {
				t.Errorf("LRU: %v must not be cached, got %v-false", i, val)
			}
		}
	}
}

func TestLRUCache(t *testing.T) {
	lru := NewLRUCache(5)
	for i := 0; i < 15; i++ {
		key := CacheKey(i)
		lru.Set(key, i)
		// cache recently cached
		val, ok := lru.Get(key)
		if !ok || val != i {
			t.Errorf("LRU: %v must be cached, got %v-%v", i, val, ok)
		}
		if i < 5 {
			continue
		}

		for j := 0; j < 15; j++ {
			val, ok := lru.Get(CacheKey(j))
			if j > i || j < i-4 {
				// must not be cached
				if ok || val == j {
					t.Errorf("LRU: %v must not be cached, got %v-%v", i, val, ok)
				}
			} else {
				// must be cached
				if !ok || val != j {
					t.Errorf("LRU: %v must be cached, got %v-%v", i, val, ok)
				}
			}
		}
	}
}

func TestOverrideUsedItems(t *testing.T) {
	lru := NewLRUCache(5)
	for i := 0; i < 15; i++ {
		key := CacheKey(i % 5)
		lru.Set(key, i)
		val, ok := lru.Get(key)
		if !ok || val != i {
			t.Errorf("LRU: %v must be cached, got %v-%v", i, val, ok)
		}
	}
}

func TestLRUCache_Panic(t *testing.T) {
	t.Run("zero-size", func(t *testing.T) {
		defer func() {
			if r := recover(); r != sizeGreaterThanZero {
				t.Error("NewLRUCache should panic for zero size")
			}
		}()
		NewLRUCache(0)
	})
	t.Run("negative-size", func(t *testing.T) {
		defer func() {
			if r := recover(); r != sizeGreaterThanZero {
				t.Error("NewLRUCache should panic for negative size")
			}
		}()
		NewLRUCache(-10)
	})
}

func benchmarking(b *testing.B, lru LRUCache) {
	b.Run("set", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			lru.Set(CacheKey(i), i)
		}
	})
	b.Run("get", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			lru.Get(CacheKey(i))
		}
	})
	b.Run("set-get", func(b *testing.B) {
		wg := sync.WaitGroup{}
		wg.Add(2)
		go func() {
			defer wg.Done()
			for i := 0; i < b.N; i++ {
				lru.Set(CacheKey(i), i)
			}
		}()
		go func() {
			defer wg.Done()
			for i := 0; i < b.N; i++ {
				lru.Get(CacheKey(i))
			}
		}()
		wg.Wait()
	})
}

func BenchmarkLRUCache(b *testing.B) {
	for size, i := 1, 1; i < 6; i++ {
		b.Run(strconv.Itoa(size), func(b *testing.B) {
			lru := NewLRUCache(size)
			benchmarking(b, lru)
		})
		size *= 10
	}
}
