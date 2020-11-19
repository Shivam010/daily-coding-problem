// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// Package solution contains Solution to Challenge #010, run
// TestSolution for test cases
package _010

import (
	"errors"
	"sync"
	"time"
)

var ErrSchedulerStopped = errors.New("scheduler has been stopped")

type Scheduler interface {
	// Schedule schedules fn after dur time with returned id until
	// it is not stopped using StopScheduling
	Schedule(fn func(), dur time.Duration) (int, error)
	// StopScheduling: stops Scheduler from scheduling any more, using
	// Schedule after StopScheduling() will return ErrSchedulerStopped
	StopScheduling()
	// Ack: helps acknowledge that the Schedule function is finished
	// using the int::id provided at time of Schedule()
	Ack() <-chan int
}

// NewScheduler creates a new scheduler
func NewScheduler() Scheduler {
	return newRunner()
}

type runner struct {
	wg   sync.WaitGroup
	list chan *job
	ack  chan int
	size int // if -1 means closed
}

func (r *runner) Schedule(fn func(), dur time.Duration) (int, error) {
	if r.size == -1 {
		return 0, ErrSchedulerStopped
	}
	r.size++
	r.list <- &job{dur: dur, fn: fn, id: r.size}
	return r.size, nil
}

func (r *runner) StopScheduling() {
	defer close(r.ack)
	r.size = -1
	close(r.list)
	r.wg.Done() // self runner goroutine
	r.wg.Wait()
}

func (r *runner) Ack() <-chan int {
	return r.ack
}

func newRunner() *runner {
	rn := &runner{
		wg:   sync.WaitGroup{},
		list: make(chan *job),
		ack:  make(chan int),
	}
	rn.run()
	return rn
}

func (r *runner) run() {
	r.wg.Add(1)
	go func() {
		for job := range r.list {
			job := job
			r.wg.Add(1)
			go func() {
				defer r.wg.Done()
				time.Sleep(job.dur)
				job.fn()
				r.ack <- job.id
			}()
		}
	}()
}

type job struct {
	id  int
	fn  func()
	dur time.Duration
}
