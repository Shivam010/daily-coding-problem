#!/usr/bin/env python3.7

# Copyright (c) 2020 Shivam Rathore. All rights reserved.
# Use of this source code is governed by MIT License that
# can be found in the LICENSE file.

# This file contains Solution to Challenge #010, run using
# time ./010/code.py


import time


def delay(f: (), milli: int):
    time.sleep(milli/1000)
    f()
    pass


def func():
    print("called")
    pass


delay(func, 1000)
