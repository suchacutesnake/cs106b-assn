// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
using namespace std;

void welcome();
void fileInput(string& fileName, int&row, int& col);
Grid<char> createGrid(string fileName, int row, int col);
void printCurrentGrid(Grid<char> grid);
void nextGrid(Grid<char> &grid, bool);
bool lifeJudge(Grid<char> grid, int rowIndex, int colIndex, bool);
void menu(Grid<char> &grid, bool);
void animate(Grid<char> &grid, bool);
bool wrapping();

int main() {
    welcome();
    string fileName;
    int row;
    int col;
    fileInput(fileName, row, col);
    bool wrap = wrapping();
    Grid<char> grid(row, col);
    grid = createGrid(fileName, row, col);
    menu(grid, wrap);
    cout << "Have a nice Life!" << endl;
    return 0;
}

void welcome() {
    cout << "Welcome to the CS 106B Game of Life,\n"
            "a simulation of the lifecycle of a bacteria colony.\n"
            "Cells (X) live and die by the following rules:\n"
            "- A cell with 1 or fewer neighbors dies.\n"
            "- Locations with 2 neighbors remain stable.\n"
            "- Locations with 3 neighbors will create life.\n"
            "- A cell with 4 or more neighbors dies.\n"<<endl;
}

void fileInput(string& fileName, int& row, int& col) {
    fileName = getLine("Grid input file name?");
    while(!fileExists(fileName)){
        cout << "Unable to open that file. Try again."<< endl;
        fileName = getLine("Grid input file name?");
    }
    ifstream fileStream;
    openFile(fileStream, fileName);
    string line;
    getline(fileStream, line);
    row = stringToInteger(line);
    getline(fileStream, line);
    col = stringToInteger(line);
    fileStream.close();
}

Grid<char> createGrid(string fileName, int row, int col){
    ifstream fileStream;
    openFile(fileStream, fileName);
    string line;
    getline(fileStream, line);
    getline(fileStream, line);
    Grid<char> grid(row, col);
    for(int i = 0; i < row; i++) {
        getline(fileStream, line);
        for(int j = 0; j < col; j++){
            grid[i][j] = line[j];
        }
    }
    fileStream.close();
    printCurrentGrid(grid);
    return grid;
}

void printCurrentGrid(Grid<char> grid) {
    char elem;
    for(int i = 0; i < grid.numRows(); i++) {
        for(int j = 0; j < grid.numCols(); j++){
            elem = grid[i][j];
            cout << elem;
        }
        cout << endl;
    }
}

bool lifeJudge(Grid<char> grid, int rowIndex, int colIndex, bool wrap) {
    int cell = 0, r, c;
    for(int i= -1; i<2; i++) {
        for(int j = -1; j<2; j++){
            if(wrap) {
                r =(rowIndex + i + grid.numRows()) % grid.numRows();
                c =(colIndex + j + grid.numCols()) % grid.numCols();
                if(grid[r][c] == 'X')
                    cell++;
            }
            else if(grid.inBounds(rowIndex + i, colIndex + j) && grid[rowIndex + i][colIndex + j]=='X')
                cell++;
        }
    }
    if(grid[rowIndex][colIndex]=='X') cell--;
    if(cell==3)
        return 1;
    else
        if(cell==2 && grid[rowIndex][colIndex]=='X')
            return 1;
    return 0;
}

void nextGrid(Grid<char> &grid, bool wrap) {
    Grid<char> nextGrid(grid.numRows(),grid.numCols());
    //to ensure that new births/deaths in that generation don't
    //impact other cells in that generation.
    for(int i = 0; i < grid.numRows(); i++) {
        for(int j = 0; j < grid.numCols(); j++) {
            if(lifeJudge(grid, i, j, wrap))
                nextGrid[i][j] = 'X';
            else
                nextGrid[i][j] = '-';
        }
    }
    grid = nextGrid;
    printCurrentGrid(grid);
}

void menu(Grid<char> &grid, bool wrap) {
    string option = getLine("a)nimate, t)ick, q)uit?");
    char opt = option.front();
    switch(opt) {
    case 'a':
    case 'A':{
        animate(grid, wrap);
        menu(grid, wrap);
        break;
    }
    case 't':
    case 'T':
        nextGrid(grid, wrap);
        menu(grid, wrap);
        break;
    case 'q':
    case 'Q':
        break;
    default:
        cout<<"Invalid choice; please try again."<<endl;
        menu(grid, wrap);
        break;
    }
}

void animate(Grid<char> &grid, bool wrap) {
    string frames = getLine("How many frames?");
    for(int i=0; i< (int)frames.length(); i++) {
        if(frames[i]-'0'>9 || frames[i]-'0'<0) { //ASCII, char to int
            cout<<"Illegal integer format. Try again."<<endl;
            frames = getLine("How many frames?");
            i = -1;
        }
    }
    int num = stringToInteger(frames);
    for(int i = 0; i < num; i++) {
        clearConsole();
        nextGrid(grid, wrap);
        pause(50);
    }
}

bool wrapping() {
    string yorn = getLine("Should the simulation wrap around the grid (y/n)?");
    char yn = yorn.front();
    switch (yn) {
    case 'y':
    case 'Y':
        return true;
    case 'n':
    case 'N':
        return false;
    default:
        cout<<"Invalid choice; please try again."<<endl;
        return wrapping();
    }
}
