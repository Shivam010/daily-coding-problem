#!/usr/bin/env python3.7

# Copyright (c) 2020 Shivam Rathore. All rights reserved.
# Use of this source code is governed by MIT License that
# can be found in the LICENSE file.

# This file contains Solution to Challenge #003, run using
# ./003/code.py


class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    pass


def serialize(n: Node) -> str:
    if n == None:
        return ""
    return n.val + "->" + serialize(n.left) + "->" + serialize(n.right)


def deserialize(s: str) -> Node:
    if s == "":
        return None
    strList = s.split("->")
    strList.reverse()

    def inner(strList) -> Node:
        if len(strList) == 0:
            return None
        pop = strList.pop()
        if pop == "":
            return None
        n = Node(pop)
        n.left = inner(strList)
        n.right = inner(strList)
        return n

    return inner(strList)


node = Node('root', Node('left', Node('left.left')), Node('right'))
assert deserialize(serialize(node)).left.left.val == node.left.left.val

node = Node('root', Node('left'), Node('right', Node('righ.righ')))
assert deserialize(serialize(node)).left.val == node.left.val
assert deserialize(serialize(node)).right.left.val == node.right.left.val
print("passed")
