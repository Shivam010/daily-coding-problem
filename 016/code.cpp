/*
Daily Coding Challenge #016
---------------------------
This problem was asked by Twitter.

You run an e-commerce website and want to record the last `N order ids` in a
log. Implement a data structure to accomplish this, with the following API:

record(order_id): adds the order_id to the log
get_last(i): gets the ith last element from the log. i is guaranteed to be
smaller than or equal to N. You should be as efficient with time and space as
possible.

Run Using
---------
g++ 016/code.cpp -o bin/out && ./bin/out < 016/in.txt > 016/out.txt
*/
#include <bits/stdc++.h>
using namespace std;

struct Store {
   private:
    // N: Max number of log ids it can store
    int N;
    // current counter
    int cnt;
    // list of log ids
    vector<string> lastIds;

   public:
    Store(int n) {
        N = n;
        cnt = 0;
        lastIds = vector<string>(n, "");
    }
    ~Store() {
        cnt = 0;
        lastIds.clear();
    }

    void record(string id) {
        lastIds[cnt] = id;
        cnt = (cnt + 1) % N;
    }
    string get_last(int i) {
        i = (cnt - i + N) % N;
        return lastIds[i];
    }
};

int main() {
    srand(time(NULL));
    Store data = Store(10);
    int t;
    cin >> t;
    while (t--) {
        string r;
        cin >> r;
        if (r == "<<") {
            int in;
            cin >> in;
            cout << data.get_last(in) << endl;
            continue;
        }
        data.record(r);
    }
}
