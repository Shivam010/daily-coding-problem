// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #056, run
// TestSolution for test cases
package _056

// Graph: the first map represent all vertices and 2nd one
// represents ending point of an edge from the key in first
type Graph map[int]map[int]struct{}

// Solution for 056: graph coloring is possible or not with at
// most k colors
func Solution(gr Graph, k int) bool {
	if len(gr) == 0 {
		return true
	}
	if k == 0 {
		return false
	}
	return colorVertex(&colorVertexReq{
		graph:         gr,
		curVertex:     0,
		totalColors:   k,
		colorOfVertex: map[int]int{},
	})
}

type colorVertexReq struct {
	graph         Graph
	curVertex     int
	totalColors   int
	colorOfVertex map[int]int
}

func colorVertex(in *colorVertexReq) bool {
	if _, ok := in.graph[in.curVertex]; !ok {
		return true
	}
one:
	for col := 0; col < in.totalColors; col++ {
		for adj := range in.graph[in.curVertex] {
			if c, ok := in.colorOfVertex[adj]; ok && c == col {
				continue one
			}
		}
		in.colorOfVertex[in.curVertex] = col
		in.curVertex++
		if colorVertex(in) {
			return true
		}
		in.curVertex--
		delete(in.colorOfVertex, in.curVertex)
	}
	return false
}
