// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "bogglegui.h"
#include "random.h"
#include "strlib.h"
#include "console.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    // TODO: implement
    if(boardText.empty())
        for(int i = 0; i < 16; i++)
            boardText.append(charToString(CUBES[i][randomInteger(0,5)]));
    else
        boardText = toUpperCase(boardText);
    BoggleGUI::labelAllCubes(boardText);
    setGrid(grid, boardText);
    dic = dictionary;
}

void Boggle::setGrid(Grid<char> &grid, string boardText) {
    grid.resize(4, 4);
    int i = 0;
    for(int r = 0; r < 4; r++) {
        for(int c = 0; c < 4; c++) {
            grid[r][c] = boardText[i];
            i++;
        }
    }
}

void Boggle::printStatus(string status) {
    clearConsole();
    cout << status << endl;
    BoggleGUI::setStatusMessage(status);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Your words (" << countHuman << "):" << wordsHuman << endl;
    cout << "Your score:" << scoreHuman << endl;
}

char Boggle::getLetter(int row, int col) {
    return grid[row - 1][col - 1];
}

bool Boggle::checkWord(string word) {
    word = toUpperCase(word);
    if(word.empty())
        return false;
    if(word.size() < 4 || wordsHuman.contains(word) || !dic.contains(word)) {
        string status = "You must enter an unfound 4+ letter word from the dictionary.";
        printStatus(status);
        return false;
    }
    return true;
}

bool Boggle::humanWordSearch(string word) {
    word = toUpperCase(word);
    if(!visitAllLetters(word))
        return false;
    countHuman++;
    scoreHuman += word.length() - 3;
    BoggleGUI::setScore(scoreHuman, BoggleGUI::HUMAN);
    wordsHuman.add(word);
    BoggleGUI::recordWord(word, BoggleGUI::HUMAN);
    return true;
}

bool Boggle::visitAllLetters(string word) {
    BoggleGUI::clearHighlighting();
    highlightedCubes.clear();
    for(int row = 0; row < grid.height(); row++) {
        for(int col = 0; col < grid.width(); col++) {
            BoggleGUI::setHighlighted(row, col, true);
            //if:find the first letter
            if(grid[row][col] == word[0]) {
                //mark the cube as highlighted
                Vector<int> cube;
                cube += row, col;
                highlightedCubes.add(cube);
                //find the other letters
                if(findNeighborHuman(word.length() - 1, word, row, col))
                    return true;
                else { //wrong first letter! shut down the light
                    highlightedCubes.remove(cube);
                    BoggleGUI::setAnimationDelay(100);
                    BoggleGUI::setHighlighted(row, col, false);
                }
            } else { //wrong first letter! Find the next one!
                BoggleGUI::setAnimationDelay(100);
                BoggleGUI::setHighlighted(row, col, false);
            }
        }
    }
    return false;//fail in finding the first letter
}

bool Boggle::findNeighborHuman(int currentWordLength, string word, int row, int col) {
    if(currentWordLength == 0)
        return true;
    int index = word.length() - currentWordLength;
    Vector<int> cube;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            int rowN = i + row, colN = j + col;
            if(grid.inBounds(rowN, colN)) {
                BoggleGUI::setHighlighted(rowN, colN, true);
                cube.clear();
                cube += rowN, colN;
                //Don't visit cubes in highlightedCubes twice!
                if(!highlightedCubes.contains(cube)) {
                    if(grid[rowN][colN] == word[index]) {
                        //mark the cube as highlighted
                        highlightedCubes.add(cube);
                        //start recursion
                        if(findNeighborHuman(currentWordLength - 1, word, rowN, colN))
                            return true;
                        else {
                            highlightedCubes.remove(cube);
                            BoggleGUI::setAnimationDelay(100);
                            BoggleGUI::setHighlighted(rowN, colN, false);
                        }
                    } else { //not the right letter
                        BoggleGUI::setAnimationDelay(100);
                        BoggleGUI::setHighlighted(rowN, colN, false);
                    }
                }
            }
        }
    }
    return false;
}

int Boggle::getScoreHuman() {
    return scoreHuman;
}

Set<string> Boggle::computerWordSearch() {
    string word;
    Vector<int> cube;
    wordsComputer.clear();
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            highlightedCubes.clear();
            word.clear();
            word += grid[i][j];
            cube.clear();
            cube += i, j;
            highlightedCubes.add(cube);
            findNeighborComputer(word, i, j);
        }
    }
    return wordsComputer;
}

void Boggle::findNeighborComputer(string word, int row, int col) {
    Vector<int> cube;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            int rowN = i + row, colN = j + col;
            cube.clear();
            cube += rowN, colN;
            //if the cube exists//avoid visiting the cube which has been visited
            if(grid.inBounds(rowN, colN) && !highlightedCubes.contains(cube)) {
                word += grid[rowN][colN];
                if(dic.containsPrefix(word)) {
                    //mark the cube as visited
                    highlightedCubes.add(cube);
                    if(word.length() < 4) {
                        //start recursion
                        findNeighborComputer(word, rowN, colN);
                    } else {
                        //check whether the word should be added
                        if(dic.contains(word) && !wordsHuman.contains(word)
                                && !wordsComputer.contains(word)) {
                            wordsComputer.add(word);
                            scoreComputer += word.length() - 3;
                            countComputer += 1;
                            BoggleGUI::recordWord(word, BoggleGUI::COMPUTER);
                        }
                        //star recursion
                        findNeighborComputer(word, rowN, colN);
                    }
                    highlightedCubes.remove(cube);
                }
                word.erase(word.length() - 1);
            }
        }
    }
}

int Boggle::getScoreComputer() {
    return scoreComputer;
}

int Boggle::getCountComputer() {
    return countComputer;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    out << boggle.grid;
    return out;
}
