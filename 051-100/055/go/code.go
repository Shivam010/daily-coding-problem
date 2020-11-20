// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #055, run
// TestSolution for test cases
package _055

import (
	"errors"
	"math"
	"math/rand"
	"sync"
	"time"
)

var (
	// ErrStorageFull: error in case of full storage
	ErrStorageFull = errors.New("urlShortener: storage is full")
	// ErrNotFound: error in case id is not found in UrlShortener.Restore
	ErrNotFound = errors.New("urlShortener: request short url not found")
	// ErrUnsupportedAlgo: error in case of unsupported algorithm in UrlShortener.Shorten
	ErrUnsupportedAlgo = errors.New("urlShortener: provided algorithm not supported")
)

const (
	// base62: base string generated using https://play.golang.org/p/5cwAWpaa2sY
	base62  = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
	baseLen = int64(len(base62))
)

// src: pseudo-random source based on start time
var src = rand.NewSource(time.Now().UnixNano())

// UrlShortener: provides the interface for any url shortener
type UrlShortener interface {
	Shorten(url string) (string, error)
	Restore(id string) (string, error)
}

// GeneratorAlgo defines the type of generator
type GeneratorAlgo int

const (
	Randomize GeneratorAlgo = iota
	Sequential
)

// inMemory implements UrlShortener in-memory
type inMemory struct {
	// mu: guards the write in size, id2url, url2id
	mu sync.Mutex

	// storage maps
	id2url map[string]string
	url2id map[string]string

	// sizes
	storageSize    int64 // # of urls shortened, currently
	shortUrlSize   int64 // size of a short id generated after shortening
	maxStorageSize int64 // max # of urls that can be shortened, based on shortUrlSize

	// generator algorithm
	algo GeneratorAlgo
}

// NewUrlShortener returns an in memory UrlShortener, using Randomize with size 6
// use options to override them
func NewUrlShortener(opts ...Option) UrlShortener {
	m := &inMemory{
		mu:     sync.Mutex{},
		id2url: map[string]string{"": ""},
		url2id: map[string]string{"": ""},
	}
	m.shortUrlSize = 6
	m.maxStorageSize = int64(math.Pow(float64(baseLen), 6))
	m.algo = Randomize
	for _, opt := range opts {
		opt.apply(m)
	}
	return m
}

// Option: helps override default configurations to in memory UrlShortener
type Option interface {
	apply(*inMemory)
}

// applier converts a apply function to Option
type applier struct{ fn func(*inMemory) }

func (a *applier) apply(m *inMemory) {
	a.fn(m)
}

func SetShortUrlSize(n int64) Option {
	return &applier{fn: func(m *inMemory) {
		m.shortUrlSize = n
		m.maxStorageSize = int64(math.Pow(float64(baseLen), float64(n)))
	}}
}

func SetGeneratorAlgorithm(algo GeneratorAlgo) Option {
	return &applier{fn: func(m *inMemory) { m.algo = algo }}
}

func (m *inMemory) Shorten(url string) (string, error) {
	m.mu.Lock()
	defer m.mu.Unlock()

	if id, ok := m.url2id[url]; ok {
		return id, nil
	}

	// storage size check
	if m.storageSize == m.maxStorageSize {
		return "", ErrStorageFull
	}

	fn := m.randomId // default is Randomize
	if m.algo == Sequential {
		fn = m.sequentialId
	} else if m.algo != Randomize {
		return "", ErrUnsupportedAlgo
	}
	id := fn(m.shortUrlSize)
	m.url2id[url] = id
	m.id2url[id] = url
	m.storageSize++
	return id, nil
}

func (m *inMemory) Restore(id string) (string, error) {
	if url, ok := m.id2url[id]; ok {
		return url, nil
	}
	return "", ErrNotFound
}

// randomId generates a unique random sourced base62 id of length n
func (m *inMemory) randomId(n int64) string {
	bid := make([]byte, n)
	for i := range bid {
		bid[i] = base62[src.Int63()%baseLen]
	}
	id := string(bid)
	if _, ok := m.id2url[id]; ok {
		return m.randomId(n)
	}
	return id
}

// sequentialId generates a unique sequential base62 id of length n
func (m *inMemory) sequentialId(n int64) string {
	bid := make([]byte, n)
	size := m.storageSize
	for i := range bid {
		i := int64(i)
		if size > 0 {
			bid[n-i-1] = base62[size%baseLen]
			size /= baseLen
		} else {
			bid[n-i-1] = base62[0]
		}
	}
	// id := string(bid)
	// if _, ok := m.id2url[id]; ok {
	// 	return m.sequentialId(n) // not possible as the storage will be full if this occurs
	// }
	return string(bid)
}
