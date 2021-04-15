// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "set.h"
#include "vector.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    void setGrid(Grid<char> &grid, string boardText);
    void printStatus(string status);
    bool visitAllLetters(string word);
    bool existsNeighbor(char ch);
    bool findNeighborHuman(int n, string word, int row, int col);
    void findNeighborComputer(string word, int row, int col);
    int getCountComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    int scoreHuman = 0, scoreComputer = 0, countHuman = 0, countComputer = 0;
    Grid<char> grid;
    Set<Vector<int>> highlightedCubes;
    Set<string> wordsHuman, wordsComputer;
    Lexicon dic;

};

#endif // _boggle_h
