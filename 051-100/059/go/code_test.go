// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _059_test

import (
	. "github.com/Shivam010/daily-coding-problem/051-100/059/go"
	"math/rand"
	"strconv"
	"testing"
)

func testAfterSync(t *testing.T, name string, sync ISync, src, des Computer) {
	t.Run(name, func(t *testing.T) {
		sync.Sync()
		if len(des) != len(src) {
			t.Fatalf("# of files, got %v want %v", len(des), len(src))
		}
		for path, file := range src {
			if f, ok := des[path]; !ok || file.Hash() != f.Hash() || !file.DataCompare(f) {
				t.Fatalf("Compare, got %v want %v", f, file)
			}
		}
		for path, file := range des {
			if _, ok := src[path]; !ok {
				t.Fatalf("File %v should not exist", file)
			}
		}
	})
}

func bytesBuffer(n int) []byte {
	data := make([]byte, n)
	rand.Read(data)
	return data
}

func TestSyncer(t *testing.T) {
	src, des := Computer{}, Computer{}

	des.CreateFile("-", bytesBuffer(10))
	des.CreateFile("0", bytesBuffer(10))
	for i := 0; i < 5; i++ {
		src.CreateFile(strconv.Itoa(i), bytesBuffer(10))
	}
	sync := NewSyncer(src, des)
	testAfterSync(t, "init", sync, src, des)

	// change data
	src["0"].Append(bytesBuffer(10))
	testAfterSync(t, "change", sync, src, des)

	src.DeleteFile("0") // delete file
	testAfterSync(t, "delete", sync, src, des)
}

var (
	syn      ISync
	src, des Computer

	list = []benchmarkParam{
		{src: 100, des: 0, size: 1000},
		{src: 100, des: 10, size: 1000},
		{src: 100, des: 100, size: 1000},
		{src: 1000, des: 100, size: 1000},
		{src: 1000, des: 100, size: 10000},
		{src: 10000, des: 10, size: 10000},
	}
	done []<-chan struct{}
)

type benchmarkParam struct {
	src  int // initial files in source
	des  int // initial files in destination
	size int // file size
}

func setupForBenchmark(b *testing.B, in benchmarkParam) ISync {
	b.Helper()
	src, des = Computer{}, Computer{}
	for i := 0; i < in.src; i++ {
		// initial files in source
		src.CreateFile(strconv.Itoa(i), bytesBuffer(in.size))
	}
	for i := 0; i < in.des; i++ {
		// initial files in destination
		des.CreateFile(strconv.Itoa(i), bytesBuffer(in.size))
	}
	return NewSyncer(src, des)
}

func BenchmarkSyncer_Async(b *testing.B) {
	for _, param := range list {
		b.Run("", func(b *testing.B) {
			done = make([]<-chan struct{}, b.N)
			for i := 0; i < b.N; i++ {
				syn = setupForBenchmark(b, param)
				done[i] = syn.Async()
			}
			for i := 0; i < b.N; i++ {
				<-done[i]
			}
		})
	}
}

func BenchmarkSyncer_Sync(b *testing.B) {
	for _, param := range list {
		b.Run("", func(b *testing.B) {
			for i := 0; i < b.N; i++ {
				syn = setupForBenchmark(b, param)
				syn.Sync()
			}
		})
	}
}
