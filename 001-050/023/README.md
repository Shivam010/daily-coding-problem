Problem: &nbsp;`#023`
------------
_Date: September 25, 2020_<br>
This problem was asked by Google.

You are given an `M by N` matrix consisting of booleans that represents a board.
Each True boolean represents a wall. Each False boolean represents a tile you
can walk on.

Given this matrix, a start coordinate, and an end coordinate, return the minimum
number of steps required to reach the end coordinate from the start. If there is
no possible path, then return null. You can move up, left, down, and right. You
cannot move through walls. You cannot wrap around the edges of the board.

For example, given the following board:

```
[[f, f, f, f],
[t, t, f, t],
[f, f, f, f],
[f, f, f, f]]
```

and start = (3, 0) (bottom left) and end = (0, 0) (top left), the minimum number
of steps required to reach the end is 7, since we would need to go through (1,
2) because there is a wall everywhere else on the second row.

**Solution(s)**:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [Golang](go/code.go)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [C++](c++/code.cpp)<br>

![]()
-----
<p align="center">
    <b><i>
        People find their paths in the strangest of ways. Let's find our own! <br>
        Let's connect <a href="https://shivam010.in">here</a>.
    </i></b>
</p>

