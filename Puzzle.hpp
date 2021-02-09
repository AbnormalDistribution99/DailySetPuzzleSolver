#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card {
    char number, color, shading, shape;
public:
    Card(char n = 0, char c = 0, char sd = 0, char sp = 0) :
        number(n), color(c), shading(sd), shape(sp) {}
    Card(string s) :
        number(s[0]), color(s[1]), shading(s[2]), shape(s[3]) {}
    
    string toString() {
        string ret("");
        ret.push_back(number);
        ret.push_back(color);
        ret.push_back(shading);
        ret.push_back(shape);
        return ret;
    }
    bool isSame(Card oth) {
        return toString() == oth.toString();
    }
    static string showCard(string sCard) {
        string ret = "";
        ret.push_back(sCard[0]);
        ret.push_back('\t');
        switch (sCard[1]) {
            case 'R':
                ret.append("red\t");
                break;
            case 'G':
                ret.append("green\t");
                break;
            case 'P':
                ret.append("purple\t");
                break;
        }
        switch (sCard[2]) {
            case 'F':
                ret.append("filled\t");
                break;
            case 'O':
                ret.append("open\t");
                break;
            case 'S':
                ret.append("striped\t");
                break;
        }
        switch (sCard[3]) {
            case 'O':
                ret.append("oval");
                break;
            case 'S':
                ret.append("squiggle");
                break;
            case 'D':
                ret.append("diamond");
                break;
        }
        return ret;
    }
    // Displays Card
    void display() {
        cout << showCard(toString()) << endl;
    }
};

// class for Puzzle which contained cards
class Puzzle {
    vector<Card> cards;
    string name;
public:
    Puzzle(string na = "") : name(na) {}

    string Name();

    int size() {
        return (int)cards.size();
    }
    string at(int);
    
    // Inserts new card
    bool push(Card);

    bool push(string);
    
    // Removes existing card.
    bool remove(Card);

    bool remove(string);

    void display();
};

#endif
