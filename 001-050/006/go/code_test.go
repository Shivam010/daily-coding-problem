// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _006

import (
	"strings"
	"testing"
)

func TestList(t *testing.T) {
	list := NewXorLinkedList()
	list.Add(1)
	get, ok := list.Get(0)
	if want := 1; !ok || get != want {
		t.Errorf("List add/get, got = %v,%v, want %v,%v", get, ok, want, true)
	}
	get, ok = list.Get(1)
	if want := 0; ok || get != want {
		t.Errorf("List add/get, got = %v,%v want %v,%v", get, ok, want, false)
	}
	list.Add(43)
	list.Add(65)
	list.Add(864)
	get, ok = list.Get(3)
	if want := 864; !ok || get != want {
		t.Errorf("List add/get, got = %v,%v want %v,%v", get, ok, want, true)
	}

	w := &strings.Builder{}
	list.Print(w)
	if want := "1 43 65 864 "; w.String() != want {
		t.Errorf("List print, got = %v, want %v", w.String(), want)
	}
}
