#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Puzzle.hpp"

using namespace std;

vector<Puzzle> puzzles;

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}
char *trim(char *s)
{
    return rtrim(ltrim(s));
}

void trim(string &str) {
    str = trim((char*)str.c_str());
}

// Checks whether all three items are the same.
bool same(char a, char b, char c) {
    if (a == b and b == c) return true;
    return false;
}
// Checks whether all three items are different.
bool differ(char a, char b,  char c) {
    if (a != b and b != c and c != a) return true;
    return false;
}
// Checks whether all three items can be a set.
bool isset(char a, char b, char c) {
    if (same(a, b, c) or differ(a, b, c)) return true;
    return false;
}
// Finds for a single characer set.
char solveSingle(char a, char b, const char s[]) {
    if (a == b) return a;
    for (int i = 0; i < 3; i++) if (s[i] != a and s[i] != b) return s[i];
    return 0;
}


int getPuzzleId(string pName, bool create = false);
// Displays the list of created puzzles.
void displayAllPuzzles();
// Displays the cards stored in the puzzle named pName.
void displayPuzzle(string pName);
// Creates new puzzle named pName.
void newPuzzle(string pName);
// Removes the specified card from the puzzle named pName.
void removeCard(string card, string pName);
// Removes the specified puzzle from the list.
void removePuzzle(string pName);

void addCard(string card, string pName);

void solveCards(string c1, string c2);
// solves the specified puzzle and displays its solution.
void solvePuzzle(string pName);

// displays whether c1, c2, and c3 form a set.
bool testCards(string c1, string c2, string c3, bool show = true);
/*
 
 PRINT INPUT DESCRPTION
 
 */

/*
 
 PRINT ERROR
 */

// main loop to handle each command
void handleCommand(stringstream &ss, string cmd) {
    if (cmd == "exit") {
        //exit program
        exit(0);
    } else if (cmd == "load") {
        string file;
        getline(ss, file, ' ');
        trim(file);
        string pName;
        getline (ss, pName, ' ');
        trim(pName);
        if (pName == "") {
            ifstream fin(file.c_str());
            while (true) {
                string str;
                getline(fin, str);
                if (str == "") break;
                stringstream fs(str);
                getline(fs, cmd, ' ');
                trim(cmd);
                handleCommand(fs, cmd);
            }
        } else {
            getline(ss, pName, ' ');
            trim(pName);
            int id = getPuzzleId(pName, true);
            ifstream fin(file.c_str());
            while (true) {
                string str;
                getline(fin, str);
                trim(str);
                if (str == "") break;
                puzzles[id].push(str);
            }
        }
    } else if (cmd == "display") {
        string tmp("");
        getline(ss, tmp, ' ');
        trim(tmp);
        if (tmp == "") displayAllPuzzles();
        else {
            displayPuzzle(tmp);
        }
    } else if (cmd == "new") {
        string pName;
        getline(ss, pName, ' ');
        trim(pName);
        newPuzzle(pName);
    } else if (cmd == "remove") {
        string s1, s2;
        getline(ss, s1, ' ');
        trim(s1);
        getline(ss, s2, ' '); // from
        getline(ss, s2, ' ');
        trim(s2);
        if (s2 != "") {
            removeCard(s1, s2);
        } else removePuzzle(s1);
    } else if (cmd == "add") {
        string s1, s2;
        getline(ss, s1, ' ');
        trim(s1);
        getline(ss, s2, ' '); //to
        getline(ss, s2, ' ');
        trim(s2);
        addCard(s1, s2);
    } else if (cmd == "solve") {
        string s1, s2;
        getline(ss, s1, ' ');
        trim(s1);
        getline(ss, s2, ' ');
        trim(s2);
        if (s2 != "") solveCards(s1, s2);
        else solvePuzzle(s1);
    } else if (cmd == "test") {
        string s1, s2, s3;
        getline(ss, s1, ' ');
        trim(s1);
        getline(ss, s2, ' ');
        trim(s2);
        getline(ss, s3, ' ');
        trim(s3);
        testCards(s1, s2, s3);
    } else {
        // Input commands may be wrong command then display this message
        cout << "Unknown Command" << endl;
    }
}


void newPuzzle(string pName) {
    puzzles.push_back(Puzzle(pName));
}
int getPuzzleId(string pName, bool create) {
    for (int i = 0; i < puzzles.size(); i++) {
        if (puzzles[i].Name() == pName) return i;
    }
    if (create) {
        newPuzzle(pName);
        return (int)puzzles.size() - 1;
    } else return -1;
}

void displayAllPuzzles() {
    for (int i = 0; i < puzzles.size(); i++) puzzles[i].display();
}
void displayPuzzle(string pName) {
    int id = getPuzzleId(pName);
    if (id == -1) cout << "No puzzle found named " << pName << endl;
    else puzzles[id].display();
}
void removeCard(string card, string pName) {
    int id = getPuzzleId(pName);
    if (id == -1) cout << "No puzzle found named " << pName << endl;
    else {
        puzzles[id].remove(card);
    }
}
void removePuzzle(string pName) {
    int id = getPuzzleId(pName);
    if (id == -1) cout << "No puzzle found named " << pName << endl;
    else puzzles.erase(puzzles.begin() + id);
}
void addCard(string card, string pName) {
    int id = getPuzzleId(pName);
    if (id == -1) cout << "No puzzle found named " << pName << endl;
    else puzzles[id].push(card);
}
void solveCards(string c1, string c2) {
    char number = solveSingle(c1[0], c2[0], "123");
    char color = solveSingle(c1[1], c2[1], "RGP");
    char shading = solveSingle(c1[2], c2[2], "FOS");
    char shape = solveSingle(c1[3], c2[3], "DOS");
    cout << number << color << shading << shape << endl;
}
void solvePuzzle(string pName) {
    int id = getPuzzleId(pName);
    if (id == -1) cout << "No puzzle found named " << pName << endl;
    Puzzle p = puzzles[id];
    for (int i = 0; i < p.size(); i++) {
        for (int j = i + 1; j < p.size(); j++) {
            for (int k = j + 1; k < p.size(); k++) {
                if (testCards(p.at(i), p.at(j), p.at(k), false)) {
                    cout << Card::showCard(p.at(i)) << "\t" << Card::showCard(p.at(j)) << "\t" << Card::showCard(p.at(k)) << endl;
                }
            }
        }
    }
}
bool testCards(string c1, string c2, string c3, bool show) {
    bool res = isset(c1[0], c2[0], c3[0]) & isset(c1[1], c2[1], c3[1])
        & isset(c1[2], c2[2], c3[2]) & isset(c1[3], c2[3], c3[3]);
    if (res) {
        if (show) cout << "Set" << endl;
        return true;
    } else {
        if (show) cout << "Not set" << endl;
        return false;
    }
}

//Main_Function:

int main(){
    string str, cmd;
    while(true){
        printInputDescription();
        getline(cin, str);
        stringstream ss(str);
        getline(ss, cmd, ' ');
        handleCommand(ss, cmd);
    }
}
