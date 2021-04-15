#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"  //getLine()
#include "filelib.h" //fileExists()
#include "strlib.h"  //stringIsInteger(), stringToInteger()
#include "map.h"
#include "random.h"  //randomInteger(min, max)
#include "vector.h"
#include "queue.h"

using namespace std;
void welcome();
string getFileName();
int valueOfN();
void buildMap(Map<Queue<string>, Vector<string>> &map, const string &fileName, const int &N);
int wordNum(const int&);
void genText(const int &num, const Map<Queue<string>, Vector<string>> &map);

int main() {
    welcome();
    string fileName = getFileName();
    int N = valueOfN();
    Map<Queue<string>, Vector<string>> map;
    buildMap(map, fileName, N);
    while(int num = wordNum(N))
        genText(num, map);
    cout << "Exiting." << endl;
    return 0;
}

void welcome() {
    cout<< "Welcome to CS 106B Random Writer ('N-Grams').\n"
           "This program makes random text based on a document.\n"
           "Give me an input file and an 'N' value for groups\n"
           "of words, and I'll create random text for you.\n" <<endl;
}

string getFileName() {
    string fileName = getLine("Input file name?");
    while(!fileExists(fileName))
        fileName = getLine("Unable to open that file. Try again.\nInput file name?");
    return fileName;
}

int valueOfN() {
    string n = getLine("Value of N?");
    if(stringIsInteger(n)) {
        int N = stringToInteger(n);
        if(N<2) {
            cout << "N must be 2 or greater." << endl;
            N = valueOfN();
        }
        return N;
    } else {
        cout << "Illegal integer format. Try again." << endl;
        int N = valueOfN();
        return N;
    }
}

void buildMap(Map<Queue<string>, Vector<string>> &map, const string &fileName, const int &N) {
    ifstream input, wrap;
    input.open(fileName);
    wrap.open(fileName);
    Queue<string> mapKey;
    Vector<string> mapValue;
    //for 3rd extra feature, create two queue in the main function
    //to track the start and end of a sentence.
    string word;

    //initialize the first key in the map
    for(int i = 0; i< N - 1; i++) {
        input >> word;
        mapKey.enqueue(word);
    }
    input >> word;
    mapValue += word;
    map.put(mapKey, mapValue);

    //build the map
    while(input >> word) {
        mapKey.dequeue();
        //enqueue the last value in the current vector to the queue
        mapKey.enqueue(mapValue.get(mapValue.size() - 1));
        if(map.containsKey(mapKey)) { //if the key exists
            mapValue = map.get(mapKey);//get the value
            mapValue += word;         //add the value
            map.put(mapKey, mapValue);//cover the old one
        } else {
            mapValue.clear();         //clear the vector
            mapValue += word;         //add the value
            map.put(mapKey, mapValue);//create a new one
        }
    }

    //wrap for N-1 more times
    for(int j = 0; j < N - 1; j++) { //same code above lol
        wrap >> word;
        mapKey.dequeue();
        mapKey.enqueue(mapValue.get(mapValue.size() - 1));
        if(map.containsKey(mapKey)) { //if the key exists
            mapValue = map.get(mapKey);//get the value
            mapValue += word;         //add the value
            map.put(mapKey, mapValue);//cover the old one
        } else {
            mapValue.clear();         //clear the vector
            mapValue += word;         //add the value
            map.put(mapKey, mapValue);//create a new one
        }
    }

    //check for the map
    //cout << map;

    input.close();
    wrap.close();
}

int wordNum(const int &N) {
    string wordnum = getLine("# of random words to generate (0 to quit)?");
    int num;
    if(stringIsInteger(wordnum)) {
        num = stringToInteger(wordnum);
        if(num != 0) {
            if(num < N) {
                cout << "Must be at least " << N << " words.\n" <<endl;
                num = wordNum(N);
            }
        } else
            return 0;
    } else {
        cout << "Illegal integer format. Try again.\n";
        num = wordNum(N);
    }
    return num;
}

//generate text
void genText(const int &num, const Map<Queue<string>, Vector<string>> &map) {
    Queue<string> window;
    Vector<string> mapValue;
    window = randomKey(map);
    cout << "...";
    for(int i = 0; i < num; i++) {
        mapValue = map.get(window);
        int r = randomInteger(0, mapValue.size() - 1);
        cout << mapValue[r] << ' ';
        window.dequeue();
        window.enqueue(mapValue[r]);
    }
    cout << "...\n" << endl;
}


