// Copyright (c) 2020 Shivam Rathore. All rights reserved.
// Use of this source code is governed by MIT License that
// can be found in the LICENSE file.

// This file contains Solution to Challenge #055, run using
// g++ 051-100/055/c++/code.cpp -o bin/out
// ./bin/out < 051-100/055/c++/in.txt > 051-100/055/c++/out.txt
#include <bits/stdc++.h>

#include <unordered_map>
using namespace std;
#define ll long long

struct UrlShortner {
   private:
    // count => number of urls in system
    int count;

    // constChar => constant base62 characters
    string constChar;
    // constInit initializes the base string
    void constInit() {
        for (int i = 0; i < 26; i++) constChar.push_back('a' + i);
        for (int i = 0; i < 26; i++) constChar.push_back('A' + i);
        for (int i = 0; i < 10; i++) constChar.push_back('0' + i);
    }
    // coverts integer to base62 strings
    string convert(int n) {
        string str = "";
        int i = 0;
        while (n) {
            i++;
            str.push_back(constChar[n % 62]);
            n /= 62;
        }
        while (i < 6) str.push_back(constChar[0]), i++;
        reverse(str.begin(), str.end());
        return str;
    }

    // key => original url | value => shorten url
    unordered_map<string, string> url_storage;
    // key => shorten url | value => original url
    unordered_map<string, string> reverse_storage;

   public:
    UrlShortner() {
        constInit();
        count = 0;
    }

    string shorten(string url) {
        unordered_map<string, string>::iterator it = url_storage.find(url);
        // url is already shortened
        if (it != url_storage.end()) return it->second;
        // new url
        string shortURL = convert(count++);
        url_storage[url] = shortURL;
        reverse_storage[shortURL] = url;
        return shortURL;
    }

    string restore(string shortURL) {
        string str = reverse_storage[shortURL];
        if (str == "") return "-";
        return str;
    }
};

int main() {
    UrlShortner shortner;

    int t;
    cin >> t;
    while (t--) {
        string op, url;
        cin >> op >> url;
        if (op == "shorten")
            cout << op << " url for url: " << url << " is \n\t"
                 << shortner.shorten(url) << endl;
        else if (op == "restore")
            cout << op << " short-url: " << url << " is \n\t"
                 << shortner.restore(url) << endl;
    }
}
