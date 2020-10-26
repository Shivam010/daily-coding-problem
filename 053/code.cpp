/*
Daily Coding Challenge #053
---------------------------
This problem was asked by Apple.

Implement a queue using two stacks. Recall that a queue is a FIFO (first-in,
first-out) data structure with the following methods: enqueue, which inserts an
element into the queue, and dequeue, which removes it.

Run Using
---------
g++ 053/code.cpp -o bin/out && ./bin/out < 053/in.txt > 053/out.txt
*/
#include <bits/stdc++.h>
using namespace std;

struct Stack {
   private:
    vector<int> data;
    int count;

   public:
    Stack() { count = 0; };
    void push(int d) {
        data.push_back(d);
        count++;
    }
    int pop() {
        if (count) {
            int d = data[--count];
            data.pop_back();
            return d;
        }
        return INT_MAX;
    }
    bool isEmpty() { return count == 0; }
};

struct Queue {
   private:
    Stack *input, *output;

   public:
    Queue() {
        input = new Stack();
        output = new Stack();
    }
    void enqueue(int d) { input->push(d); }
    int dequeue() {
        if (input->isEmpty() && output->isEmpty()) return INT_MAX;
        if (output->isEmpty()) {
            while (!input->isEmpty()) output->push(input->pop());
        }
        return output->pop();
    }
    bool isEmpty() { return input->isEmpty() && output->isEmpty(); }
};

int main() {
    int t;
    cin >> t;
    Queue *qu = new Queue();
    while (t--) {
        string op;
        int val;
        cin >> op;
        if (op == "enqueue") {
            cin >> val;
            qu->enqueue(val);
        } else if (op == "dequeue") {
            val = qu->dequeue();
            if (val == INT_MAX)
                cout << "empty" << endl;
            else
                cout << val << endl;
        }
    }
}
