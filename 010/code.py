#!/usr/bin/env python3.7

"""
Daily Coding Challenge #010
---------------------------
This problem was asked by Apple.

Implement a job scheduler which takes in a function f and an integer n, and
calls f after n milliseconds.

Run Using
---------
time ./010/code.py
"""

import time


def delay(f: (), milli: int):
    time.sleep(milli/1000)
    f()
    pass


def func():
    print("called")
    pass


delay(func, 1000)
