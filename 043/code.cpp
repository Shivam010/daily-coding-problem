/*
Daily Coding Challenge #043
---------------------------
This problem was asked by Amazon.

Implement a stack that has the following methods:

- `push(val)`, which pushes an element onto the stack
- `pop()`, which pops off and returns the topmost element of the stack. If there
are no elements in the stack, then it should throw an error or return null.
- `max()`, which returns the maximum value in the stack currently. If there are
no elements in the stack, then it should throw an error or return null.

Each method should run in constant time.

Run Using
---------
g++ 043/code.cpp -o bin/out && ./bin/out < 043/in.txt > 043/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Stack {
   private:
    int len;
    vector<ll> main;
    vector<ll> largest;

   public:
    Stack() {
        main = vector<ll>();
        largest = vector<ll>();
        len = 0;
    }
    ~Stack() {
        main.clear();
        largest.clear();
    }

    // push
    void push(ll val) {
        main.push_back(val);
        if (len > 0 && largest[len - 1] > val) val = largest[len - 1];
        largest.push_back(val);
        len++;
    }
    // pop
    ll pop() {
        if (len == 0) throw "No element in stack";
        ll p = main[--len];
        main.pop_back();
        largest.pop_back();
        return p;
    }
    // max
    ll max() {
        if (len == 0) throw "No element in stack";
        return largest[len - 1];
    }
};

void solve(Stack& st) {
    ll val;
    string op;
    cin >> op;
    if (op == "push") {
        cin >> val;
        st.push(val);
        cout << "pushed: " << val << endl;
        return;
    }
    if (op == "pop") {
        cout << "poped: " << st.pop() << endl;
        return;
    }
    if (op == "max") {
        cout << "max: " << st.max() << endl;
    }
}

int main() {
    int t;
    cin >> t;
    Stack st;
    while (t--) {
        try {
            solve(st);
        } catch (char const* e) {
            cout << "error: " << e << endl;
        }
    }
}
