Problem: &nbsp;`#003`
------------
[![Open for Review](https://img.shields.io/badge/open-for%20reviews-brightgreen?style=plastic)](https://github.com/Shivam010/daily-coding-problem/issues)
[![Python](https://img.shields.io/badge/solution-Python-brightgreen?style=plastic)](python/code.py)
[![MIT License](https://img.shields.io/github/license/Shivam010/daily-coding-problem?style=plastic)](https://github.com/Shivam010/daily-coding-problem/blob/master/LICENSE)

_Date: September 05, 2020_<br>
This problem was asked by Google.

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

**Solution(s)**:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [Python](python/code.py)<br>

[]()
-----
<p align="center">
    <b><i>
	    People find their paths in the strangest of ways. Let's find our own! <br>
	    Let's connect <a href="https://shivam010.in">here</a>.
	</i></b>
</p>
