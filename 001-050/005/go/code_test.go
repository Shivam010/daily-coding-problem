// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _005

import (
	"reflect"
	"strconv"
	"testing"
)

func TestSolution(t *testing.T) {
	tests := []struct {
		first, second interface{}
	}{
		{3, 4},
		{"one", "two"},
		{struct{}{}, nil},
		{map[struct{}]struct{}{{}: {}}, []string{""}},
	}
	for i, tt := range tests {
		t.Run(strconv.Itoa(i), func(t *testing.T) {
			t.Run("car", func(t *testing.T) {
				if got := Car(Cons(tt.first, tt.second)); !reflect.DeepEqual(got, tt.first) {
					t.Errorf("Car(Cons(...)) = %v, want %v", got, tt.first)
				}
			})
			t.Run("cdr", func(t *testing.T) {
				if got := Cdr(Cons(tt.first, tt.second)); !reflect.DeepEqual(got, tt.second) {
					t.Errorf("Cdr(Cons(...)) = %v, want %v", got, tt.second)
				}
			})
		})
	}
}
