#!/usr/bin/env python3.7

"""
Daily Coding Challenge #003
---------------------------
Given the root to a binary tree, implement serialize(root), which serializes 
the tree into a string, and deserialize(s), which deserializes the string 
back into the tree.

For example, given the following Node class

    class Node:
        def __init__(self, val, left=None, right=None):
            self.val = val
            self.left = left
            self.right = right
    The following test should pass:

    node = Node('root', Node('left', Node('left.left')), Node('right'))
    assert deserialize(serialize(node)).left.left.val == 'left.left'

Run Using
---------
./003/code.py
"""


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
