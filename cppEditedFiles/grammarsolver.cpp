/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "map.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
void next(string symbol, Map<string, Vector<string>>& map, string& outLine) {
    Vector<string> mapValue = map[symbol], v;
    string nextSymbol = mapValue[randomInteger(0, mapValue.size() - 1)];
    v = stringSplit(nextSymbol, " ");
    for(int i = 0; i < v.size(); i++) {
        if(!map.containsKey(v[i]))
            outLine += v[i] + ' ';
        else
            next(v[i], map, outLine);
    }
}

Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    if(times <= 0)
        return {};
    string line, mapKey, rules, nextSymbol, outLine;
    Vector<string> v, mapValue, output;
    Map<string, Vector<string>> map;
    //Part 1: Reading the Input File
    while(getline(input, line)) {
        v = stringSplit(line, "::=");
        mapKey = v[0];
        if(map.containsKey(mapKey)) {
            cout << "The grammar contains more than one line for the same non-terminal.\n"
                    "Please check your grammar text." << endl;
            return {};
        }
        rules.clear();
        for(int i = 1; i < v.size(); i++) {
            rules += v[i];
        }
        mapValue = stringSplit(rules, "|");
        map.put(mapKey, mapValue);
        mapValue.clear();
        v.clear();
    }

    //Part 2: Generating Random Expansions from the Grammar
    for(int j = 0; j < times; j++) {
        mapValue = map[symbol];//first symbol
        nextSymbol = mapValue[randomInteger(0, mapValue.size() - 1)];//pick one of the rules
        v = stringSplit(nextSymbol, " ");//separate the symbols
        for(int i = 0; i < v.size(); i++) {
            next(v[i], map, outLine);
        }
        output += trim(outLine);
        outLine.clear();
    }
    return output;
}
