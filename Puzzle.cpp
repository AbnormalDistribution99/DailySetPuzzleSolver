#ifndef PUZZLE_CPP
#define PUZZLE_CPP

#include "Puzzle.hpp"
#include <iostream>
using namespace std;

bool Puzzle::push(Card nCard) {
    if (cards.size() == 12) {
        cout << "This puzzle already has 12 cards" << endl;
        return false;
    }
    cards.push_back(nCard);
    return true;
}

bool Puzzle::push(string sCard) {
    return push(Card(sCard));
}

bool Puzzle::remove(Card rCard) {
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i].isSame(rCard)) {
            cards.erase(cards.begin() + i);
            return true;
        }
    }
    return false;
}

bool Puzzle::remove(string sCard) {
    return remove(Card(sCard));
}
string Puzzle::at(int i) {
    return cards[i].toString();
}

void Puzzle::display() {
    cout << "Puzzle Name : " << name << endl;
    for (int i = 0; i < cards.size(); i++) cards[i].display();
    cout << endl;
}

string Puzzle::Name() {
    return name;
}

#endif
