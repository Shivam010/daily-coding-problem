// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _061

import (
	"fmt"
	"math"
	"reflect"
	"testing"
)

func TestSolution(t *testing.T) {
	for x := 0; x <= 12; x++ {
		for y := 0; y <= 15; y++ {
			t.Run(fmt.Sprintf("%v^%v", x, y), func(t *testing.T) {
				got := Solution(x, y)
				want := int(math.Pow(float64(x), float64(y)))
				if !reflect.DeepEqual(got, want) {
					t.Errorf("Solution() = %v, want %v", got, want)
				}
			})
		}
	}

}
