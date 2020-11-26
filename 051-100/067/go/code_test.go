// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _067

import (
	"math/rand"
	"strconv"
	"sync"
	"testing"
)

func TestCache(t *testing.T) {
	lfu := NewLFUCache(20)
	for i := 0; i < 10; i++ {
		lfu.Set(CacheKey(i), i)
	}
	for i := 10; i < 20; i++ {
		lfu.Set(CacheKey(i), strconv.Itoa(i))
	}
	for i := 0; i < 30; i++ {
		val, ok := lfu.Get(CacheKey(i))
		if i < 20 {
			if !ok {
				t.Errorf("LFU: %v must be cached, got %v", i, ok)
			}
			if val == nil {
				t.Errorf("LFU: %v must be cached, got nil-true", i)
			}
		}
		if i < 10 {
			in, ok := val.(int)
			if !ok || in != i {
				t.Errorf("LFU: int(%v) must be returned, got %v of type:%T", i, in, in)
			}
		}
		if i >= 10 && i < 20 {
			in, ok := val.(string)
			if !ok || in != strconv.Itoa(i) {
				t.Errorf("LFU: string(%v) must be returned, got %v of type:%T", i, in, in)
			}
		}
		if i >= 20 {
			if ok {
				t.Errorf("LFU: %v must not be cached, got %v", i, ok)
			}
			if val != nil {
				t.Errorf("LFU: %v must not be cached, got %v-false", i, val)
			}
		}
	}
}

func TestLFUCache(t *testing.T) {
	must := func(want interface{}) func(val interface{}, ok bool) {
		return func(val interface{}, ok bool) {
			if !ok || val != want {
				t.Errorf("LFU: %v must be cached, got %v-%v", want, val, ok)
			}
		}
	}
	mustNot := func(want interface{}) func(val interface{}, ok bool) {
		return func(val interface{}, ok bool) {
			if ok || val != nil {
				t.Errorf("LFU: %v must not be cached, got %v-%v", want, val, ok)
			}
		}
	}

	lfu := NewLFUCache(5)

	// Set new keys: all will have 1 freq (1st iteration)
	for i := -1; i < 4; i++ {
		key := CacheKey(i)
		lfu.Set(key, key)
	}

	// Now, set for 4 must remove a key and as all have same
	// freq, least recently used key (-1) should be removed
	key := CacheKey(4)
	lfu.Set(key, key)

	// -1 should not be found
	key = CacheKey(-1)
	mustNot(key)(lfu.Get(key))

	// update some key's freq
	key1 := CacheKey(rand.Intn(5)) // key with freq one
	key2 := (key1 + 1) % 5
	key3 := (key1 + 2) % 5
	key4 := (key1 + 3) % 5
	key5 := (key1 + 4) % 5

	// 2nd iteration
	must(key2)(lfu.Get(key2))
	must(key3)(lfu.Get(key3))
	must(key4)(lfu.Get(key4))
	must(key5)(lfu.Get(key5))

	// Now, set for 5 must remove the key1, as it has least frequency
	key = CacheKey(5)
	lfu.Set(key, key)
	mustNot(key1)(lfu.Get(key1))

	// Now, 3rd iteration will make frequencies of:
	// key2 -> 2 from 2
	// key3 -> 3 from 2
	// key4 -> 4 from 2
	// key5 -> 5 from 2
	// key -> 6 from 1
	// making key2 least frequent

	// key3 will have frequency 3
	lfu.Set(key3, CacheKey(rand.Int()))

	// key4 will have frequency 4
	lfu.Set(key4, CacheKey(rand.Int()))
	lfu.Set(key4, CacheKey(rand.Int()))

	// key5 will have frequency 5
	lfu.Set(key5, CacheKey(rand.Int()))
	lfu.Set(key5, CacheKey(rand.Int()))
	lfu.Set(key5, CacheKey(rand.Int()))

	// key will have frequency 6
	for i := 1; i < 6; i++ {
		lfu.Set(key, CacheKey(rand.Int()))
	}

	// hence, adding any new key will result in removal of key2
	lfu.Set(CacheKey(rand.Int())+6, CacheKey(rand.Int())) // +6 is done to ensure a new key will be added
	mustNot(key2)(lfu.Get(key2))
}

func TestOverrideUsedItems(t *testing.T) {
	lfu := NewLFUCache(3)
	for i := 0; i < 15; i++ {
		key := CacheKey(i % 3)
		if i > 5 {
			key = CacheKey(i % 4)
		}
		lfu.Set(key, i)
		val, ok := lfu.Get(key)
		if !ok || val != i {
			t.Errorf("LFU: %v must be cached, got %v-%v", i, val, ok)
		}
	}
}

func TestLFUCache_Panic(t *testing.T) {
	t.Run("zero-size", func(t *testing.T) {
		defer func() {
			if r := recover(); r != sizeGreaterThanZero {
				t.Error("NewLFUCache should panic for zero size")
			}
		}()
		NewLFUCache(0)
	})
	t.Run("negative-size", func(t *testing.T) {
		defer func() {
			if r := recover(); r != sizeGreaterThanZero {
				t.Error("NewLFUCache should panic for negative size")
			}
		}()
		NewLFUCache(-10)
	})
	t.Run("one-size", func(t *testing.T) {
		lfu := NewLFUCache(1)
		for i := 0; i < 10; i++ {
			lfu.Set(CacheKey(i), i)
			val, ok := lfu.Get(CacheKey(i))
			if !ok || val != i {
				t.Errorf("LFU: %v must be cached, got %v-%v", i, val, ok)
			}
		}
	})
}

func benchmarking(b *testing.B, lfu LFUCache) {
	b.Run("set", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			lfu.Set(CacheKey(i), i)
		}
	})
	b.Run("get", func(b *testing.B) {
		for i := 0; i < b.N; i++ {
			lfu.Get(CacheKey(i))
		}
	})
	b.Run("set-get", func(b *testing.B) {
		wg := sync.WaitGroup{}
		wg.Add(2)
		go func() {
			defer wg.Done()
			for i := 0; i < b.N; i++ {
				lfu.Set(CacheKey(i), i)
			}
		}()
		go func() {
			defer wg.Done()
			for i := 0; i < b.N; i++ {
				lfu.Get(CacheKey(i))
			}
		}()
		wg.Wait()
	})
}

func BenchmarkLFUCache(b *testing.B) {
	for size, i := 1, 1; i < 6; i++ {
		b.Run(strconv.Itoa(size), func(b *testing.B) {
			lfu := NewLFUCache(size)
			benchmarking(b, lfu)
		})
		size *= 10
	}
}
