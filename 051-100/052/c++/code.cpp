// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #052, run using
// g++ 052/code.cpp -o b`in/out && ./bin/out < 052/in.txt > 052/out.txt
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node {
   private:
    // isNullHeader: for identifing header & footer in LRU and null key, value
    bool isNullHeader;

   public:
    int key;
    int value;
    Node *prev;
    Node *next;

    Node(int k, int v, bool isNull = false) {
        key = k;
        value = v;
        isNullHeader = isNull;
        prev = next = NULL;
    }
};

struct LRU {
   private:
    int limit;
    map<int, Node *> data;

    // header is the starting head of the LRU
    // header will have least recently used node in its next.
    Node *header;
    // footer is the end part or tail of the LRU
    // footer will have most recently used node in its prev.
    Node *footer;

   public:
    LRU(int n) {
        limit = n;
        header = new Node(0, 0, true);
        footer = new Node(0, 0, true);
        header->next = footer;
        footer->prev = header;
    };

    void remove(Node *node) {
        (node->prev)->next = node->next;
        (node->next)->prev = node->prev;
    }

    void insert(Node *node) {
        (footer->prev)->next = node;
        node->prev = footer->prev;
        node->next = footer;
        footer->prev = node;
    }

    void set(int key, int value) {
        map<int, Node *>::iterator it = data.find(key);
        if (it != data.end()) remove(it->second), data.erase(it);
        Node *node = new Node(key, value);
        data[key] = node;
        insert(node);
        // if limit is reached remove least recently used entry (i.e. first one)
        if (limit < data.size()) {
            node = header->next;
            remove(node);
            data.erase(node->key);
        }
    }

    Node *get(int key) {
        map<int, Node *>::iterator it = data.find(key);
        if (it == data.end()) return NULL;
        Node *node = it->second;
        // remove and reinsert the node, so that it is marked as recently used
        remove(node);
        insert(node);
        return node;
    }

    int size() { return data.size(); }

    void printCache() {
        // in order of recently used
        Node *cur = footer;
        while (cur != NULL) {
            cout << " " << cur->key << ".." << cur->value << " ";
            cur = cur->prev;
        }
    }
};

int main() {
    int limit;
    cin >> limit;
    LRU *cache = new LRU(limit);

    int op;  // no. of operations
    cin >> op;
    while (op--) {
        string fn;
        cin >> fn;
        int key, value;
        cin >> key;
        if (fn == "set") {
            cin >> value;
            cache->set(key, value);
            cout << "Key Value pair is stored: " << key << ".." << value << endl;
        } else if (fn == "get") {
            Node *node = cache->get(key);
            if (node == NULL)
                cout << "Key: "<<key<<" Not Found" << endl;
            else
                cout << "Value of key: " << key << " is " << node->value
                     << endl;
        }
        cout << "\t\t\t\t\t\t\t\t\t\t\t";
        cout << "Size of cache: " << cache->size() << " -> ";
        cache->printCache();
        cout << endl;
    }
}
