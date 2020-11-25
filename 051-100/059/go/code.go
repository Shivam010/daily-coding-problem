// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #059, run
// TestSolution for test cases
package _059

import (
	"bytes"
	"crypto/md5"
	"sync"
)

// ISync provides interface for file syncing
type ISync interface {
	Sync()
	Async() <-chan struct{}
}

func NewSyncer(src, des Computer) ISync {
	return &syncer{source: src, destination: des}
}

// syncer implements file syncing algorithm for two computers using ISync
type syncer struct {
	mu sync.Mutex

	source      Computer // our source computer
	destination Computer // our destination computer
}

// Sync runs the synchronous syncing of files
func (s *syncer) Sync() {
	s.mu.Lock()
	defer s.mu.Unlock()

	notDel := map[string]struct{}{}
	for path, src := range s.source {
		notDel[path] = struct{}{}
		if des, ok := s.destination[path]; ok && des.hash == src.hash {
			continue
		}
		s.destination.CreateFile(path, src.data)
	}
	for path := range s.destination {
		if _, ok := notDel[path]; !ok {
			s.destination.DeleteFile(path)
		}
	}
}

// Async runs the asynchronous syncing and returns a done channel
func (s *syncer) Async() <-chan struct{} {
	s.mu.Lock()
	defer s.mu.Unlock()

	done := make(chan struct{}, 1)
	go func() {
		s.Sync()
		done <- struct{}{}
	}()
	return done
}

// Computer represents our in-memory computer for the challenge
type Computer map[string]*File

func (com Computer) CreateFile(path string, data []byte) {
	if f, ok := com[path]; ok {
		f.Write(data)
	} else {
		com[path] = NewFile(path, data)
	}
}

func (com Computer) DeleteFile(path string) {
	delete(com, path)
}

type Md5hash [md5.Size]byte

// File represents our in-memory file for the challenge
type File struct {
	path string // full-path including name
	data []byte
	hash Md5hash
}

func NewFile(path string, data []byte) *File {
	f := &File{path: path}
	f.Write(data)
	return f
}

func (f *File) Append(b []byte) {
	f.data = append(f.data, b...)
	f.hash = md5.Sum(f.data)
}

func (f *File) Write(b []byte) {
	f.data = nil
	f.Append(b)
}

func (f *File) DataCompare(b *File) bool {
	if b == nil {
		return f == nil
	}
	return bytes.Compare(f.data, b.data) == 0
}

func (f *File) Path() string  { return f.path }                      // returns path of file
func (f *File) Hash() Md5hash { return f.hash }                      // returns hash of file
func (f *File) Data() []byte  { return append([]byte{}, f.data...) } // returns a copy of data
