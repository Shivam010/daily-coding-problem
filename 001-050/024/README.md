Problem: &nbsp;`#024`
------------
[![Open for Review](https://img.shields.io/badge/open-for%20reviews-brightgreen?style=plastic)](https://github.com/Shivam010/daily-coding-problem/issues)
[![C++](https://img.shields.io/badge/solution-C++-brightgreen?style=plastic)](c++/code.cpp)
[![MIT License](https://img.shields.io/github/license/Shivam010/daily-coding-problem?style=plastic)](https://github.com/Shivam010/daily-coding-problem/blob/master/LICENSE)

_Date: September 26, 2020_<br>
This problem was asked by Google.

Implement locking in a binary tree. A binary tree node can be locked or unlocked
only if all of its descendants or ancestors are not locked.

Design a binary tree node class with the following methods:

- `is_locked`, which returns whether the node is locked.
- `lock`, which attempts to lock the node. If it cannot be locked, then it
should return false. Otherwise, it should lock it and return true.
- `unlock`, which unlocks the node. If it cannot be unlocked, then it should
return false. Otherwise, it should unlock it and return true.

You may augment the node to add parent pointers or any other property you would
like. You may assume the class is used in a single-threaded program, so there is
no need for actual locks or mutexes. Each method should run in `O(h)`, where `h`
is the height of the tree.

**Solution(s)**:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [C++](c++/code.cpp)<br>

[]()
-----
<p align="center">
    <b><i>
	    People find their paths in the strangest of ways. Let's find our own! <br>
	    Let's connect <a href="https://shivam010.in">here</a>.
	</i></b>
</p>
