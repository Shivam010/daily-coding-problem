// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #053, run using
// g++ 053/code.cpp -o bin/out && ./bin/out < 053/in.txt > 053/out.txt
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
