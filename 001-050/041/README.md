Problem: &nbsp;`#041`
------------
_Date: October 13, 2020_<br>
This problem was asked by Facebook.

Given an unordered list of flights taken by someone, each represented as
(origin, destination) pairs, and a starting airport, compute the person's
itinerary. If no such itinerary exists, return null. If there are multiple
possible itineraries, return the lexicographically smallest one. All flights
must be used in the itinerary.

For example, given the list of flights [('SFO', 'HKO'), ('YYZ', 'SFO'), ('YUL',
'YYZ'), ('HKO', 'ORD')] and starting airport 'YUL', you should return the list
['YUL', 'YYZ', 'SFO', 'HKO', 'ORD'].

Given the list of flights [('SFO', 'COM'), ('COM', 'YYZ')] and starting airport
'COM', you should return null.

Given the list of flights [('A', 'B'), ('A', 'C'), ('B', 'C'), ('C', 'A')] and
starting airport 'A', you should return the list ['A', 'B', 'C', 'A', 'C'] even
though ['A', 'C', 'A', 'B', 'C'] is also a valid itinerary. However, the first
one is lexicographically smaller.

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

