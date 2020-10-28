/*
Daily Coding Challenge #055
---------------------------
This problem was asked by Microsoft.

Implement a URL shortener with the following methods:

- `shorten(url)`, which shortens the url into a six-character alphanumeric
string, such as `zLg6wl`.
- `restore(short)`, which expands the shortened string into the original url. If
no such shortened string exists, return null.

Hint: What if we enter the same URL twice?

Run Using
---------
g++ 055/code.cpp -o bin/out && ./bin/out < 055/in.txt > 055/out.txt
*/
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
