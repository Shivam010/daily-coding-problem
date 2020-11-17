Problem: &nbsp;`#018`
------------
_Date: September 20, 2020_<br>
This problem was asked by Google.

Given an array of integers and a number k, where `1 <= k <= length` of the
array, compute the maximum values of each subarray of length k.

For example, given `array = [10, 5, 2, 7, 8, 7]` and `k = 3`, we should get:
`[10, 7, 8, 8]`, since:

    10 = max(10, 5, 2)
    7 = max(5, 2, 7)
    8 = max(2, 7, 8)
    8 = max(7, 8, 7)

Do this in `O(n)` time and `O(k)` space. You can modify the input array in-place
and you do not need to store the results. You can simply print them out as you
compute them.

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

