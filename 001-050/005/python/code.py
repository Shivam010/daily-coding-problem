#!/usr/bin/env python3.7

# Copyright (c) 2020 Shivam Rathore. All rights reserved.
# Use of this source code is governed by MIT License that
# can be found in the LICENSE file.

# This file contains Solution to Challenge #005, run using
# ./005/code.py


def cons(a, b):
    def pair(f):
        return f(a, b)
    return pair


def car(pair):
    def first(a, b):
        return a
    return pair(first)


def cdr(pair):
    def second(a, b):
        return b
    return pair(second)


assert car(cons(3, 4)) == 3
assert cdr(cons(3, 4)) == 4

assert cons(3, 4)(print) == None
print("passed")
