// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

package _010

import (
	"testing"
	"time"
)

func nilError(t *testing.T, err error) {
	t.Helper()
	if err != nil {
		t.Error(err, "error should be nil")
	}
}

func TestScheduler(t *testing.T) {
	fn := func(d time.Duration) (func(), time.Duration) {
		return func() { t.Log("ran after", d) }, d
	}

	mp, cnt := map[int]struct{}{}, 0
	check := func(id int, err error) {
		cnt++
		nilError(t, err)
		if _, ok := mp[id]; ok {
			t.Error("scheduled fn id must be unique")
		}
		mp[id] = struct{}{}
	}

	// scheduler
	sch := NewScheduler()

	// acknowledgement
	done := make(chan struct{})
	go func() {
		for id := range sch.Ack() {
			if id > cnt || id < 0 {
				t.Error("acknowledged id must be among the ids of scheduler", "id", id)
			}
		}
		done <- struct{}{}
	}()

	check(sch.Schedule(fn(time.Second)))
	check(sch.Schedule(fn(time.Millisecond)))
	check(sch.Schedule(fn(100 * time.Nanosecond)))

	// stop scheduling
	sch.StopScheduling()

	// try adding again
	if _, err := sch.Schedule(fn(time.Second)); err != ErrSchedulerStopped {
		t.Error("ErrSchedulerStopped error should be returned")
	}

	<-done
}
