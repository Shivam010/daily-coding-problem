Problem: &nbsp;`#005`
------------
_Date: September 07, 2020_<br>
This problem was asked by Jane Street.

`cons(a, b)` constructs a pair, and `car(pair)` and `cdr(pair)` returns the 
first and last element of that pair. For example, `car(cons(3, 4))` returns 
`3`, and `cdr(cons(3, 4))` returns `4`.

Given this implementation of cons:

    def cons(a, b):
        def pair(f):
            return f(a, b)
        return pair

Implement `car` and `cdr`.

**Solution(s)**:<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [Golang](go/code.go)<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    • [Python](python/code.py)<br>

![]()
-----
<p align="center">
    <b><i>
        People find their paths in the strangest of ways. Let's find our own! <br>
        Let's connect <a href="https://shivam010.in">here</a>.
    </i></b>
</p>

