// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _062

import (
	"fmt"
	"reflect"
	"testing"
)

func TestSolution(t *testing.T) {
	sol := [][]int64{{1}}
	for i := 0; i < 11; i++ {
		row := make([]int64, 0, len(sol)+1)
		for i := range sol {
			if i == 0 {
				row = append(row, 1)
				sol[i] = append(sol[i], 1)
				continue
			}
			ln := len(sol[i])
			x := sol[i-1][ln] + sol[i][ln-1]
			row = append(row, x)
			sol[i] = append(sol[i], x)
		}
		ln := len(row)
		row = append(row, row[ln-1]*2)
		//fmt.Println(i, row, sol)
		sol = append(sol, row)
	}
	//for _, l := range sol {
	//	for _, i := range l {
	//		fmt.Printf("%v,", i)
	//	}
	//	fmt.Println()
	//}
	for i := int64(1); i <= 10; i++ {
		for j := int64(1); j <= 10; j++ {
			t.Run(fmt.Sprintf("%v,%v", i, j), func(t *testing.T) {
				if got := Solution(i, j); !reflect.DeepEqual(got, sol[i-1][j-1]) {
					t.Errorf("Solution() = %v, want %v", got, sol[i-1][j-1])
				}
			})
		}
	}
}
