Other Problem: &nbsp;`#002`
------------
_Date: October 18, 2020_<br>
This problem was asked by Turvo.

You are given a tree consisting of `N` vertices, rooted at vertex `1`. Each
vertex consists of a lowercase English alphabet as a node value.

If the ancestor node has the same node value as that of any vertex then that
ancestor node is considered as its valid parent vertex.

Your task is to detach all the nodes from the tree and attach them to any of the
valid parent vertices (in the initial tree) and print the number of connected
components obtained.

For example, the following tree:
```
    1(a)
    /
  2(a)
   \
   3(b)
    \
    4(a)
```
will have 2 connected components:
```
    1(a)
    /   \      and    3(b)
  2(a)  4(a)
```

**Solution(s)**:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [C++](code.cpp)<br>

![]()
-----
<p align="center">
    <b><i>
        People find their paths in the strangest of ways. Let's find our own! <br>
        Let's connect <a href="https://shivam010.in">here</a>.
    </i></b>
</p>
