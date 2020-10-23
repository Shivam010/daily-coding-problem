/*
Daily Coding Challenge #051
---------------------------
This problem was asked by Facebook.

Given a function that generates perfectly random numbers between 1 and k
(inclusive), where k is an input, write a function that shuffles a deck of cards
represented as an array using only swaps.

It should run in O(N) time.

Hint: Make sure each one of the 52! permutations of the deck is equally likely.

Run Using
---------
g++ 051/code.cpp -o bin/out && ./bin/out < 051/in.txt > 051/out.txt
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int random(int k) { return rand() % k; }

void shuffle(pair<char, int> *deck) {
    for (int i = 0; i < 52; i++) {
        pair<char, int> tmp = deck[i];
        int in = random(52);
        deck[i] = deck[in];
        deck[in] = tmp;
    }
    return;
}

int main() {
    string suit = "CDHS";  // Suit of card: Club Diamonds Hearts Spade
    srand(time(NULL));
    int t;
    cin >> t;
    pair<char, int> sortedDeck[52];
    for (int i = 0; i < 52; i++) {
        sortedDeck[i] = make_pair(suit[i / 13], 1 + i % 13);
        cout << sortedDeck[i].first << "-" << sortedDeck[i].second << " ";
    }
    cout << endl << endl;

    while (t--) {
        int used[52] = {0};  // All cards

        pair<char, int> deck[52];

        for (int i = 0; i < 52; i++) {
            int card = rand() % 52;
            while (used[card]) card = rand() % 52;
            deck[i] = make_pair(suit[card / 13], 1 + card % 13);
            used[card] = 1;
        }

        shuffle(deck);
        for (int i = 0; i < 52; i++)
            cout << deck[i].first << "-" << deck[i].second << " ";
        cout << endl;

        sort(deck, deck + 52);
        for (int i = 0; i < 52; i++)
            if (deck[i] != sortedDeck[i]) throw "Shuffle is wrong";
    }
}
