#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "filelib.h"
#include "strlib.h"
#include "queue.h"
#include "stack.h"

using namespace std;

void welcome();
void getDic(string& dicName, Lexicon& dic);
bool input(string& word1, string& word2, const Lexicon& dic);
void wordladder(const string& word1, const string& word2, const Lexicon dic);
bool neighbor(const string&, const string&, Queue<Stack<string>>&, const Lexicon, Lexicon&);
void popStack(Stack<string>& stack, const string& word1, const string& word2);

int main() {
    string word1, word2, dicName;
    Lexicon dic;
    getDic(dicName, dic);
    while(input(word1, word2, dic))
        wordladder(word1, word2, dic);
    cout << "Have a nice day." << endl;
    return 0;
}

void welcome() {
    cout << "Welcome to CS 106B Word Ladder.\n"
            "Please give me two English words, and I will change the\n"
            "first into the second by changing one letter at a time.\n";
}

void getDic(string& dicName, Lexicon& dic) {
    dicName = getLine("Dictionary file name?");
    while(!fileExists(dicName))
        dicName = getLine("Unable to open that file.  Try again.\nDictionary file name?");
    dic.addWordsFromFile(dicName);
}

bool input(string& word1, string& word2, const Lexicon& dic) {
    word1 = getLine("Word #1 (or Enter to quit):");
    if(word1.empty())
        return false;
    word2 = getLine("Word #2 (or Enter to quit):");
    if(word2.empty())
        return false;
    word1 = toLowerCase(word1);
    word2 = toLowerCase(word2);
    if(word1 == word2) {
        cout << "The two words must be different.\n" << endl;
        if(!input(word1, word2, dic))
            return false;
    }
    else if(word1.size() != word2.size()) {
        cout << "The two words must be the same length.\n" << endl;
        if(!input(word1, word2, dic))
            return false;
    }
    else if(!(dic.contains(word1) && dic.contains(word2))) {
        cout << "The two words must be found in the dictionary.\n" << endl;
        if(!input(word1, word2, dic))
            return false;
    }
    return true;
}

void wordladder(const string& word1, const string& word2, const Lexicon dic) {
    Queue<Stack<string>> queue;
    Stack<string> stack;
    Lexicon words;//to track words used
    stack.push(word1);
    words.add(word1);
    queue.enqueue(stack);
    while(!queue.isEmpty()) {
        if(neighbor(word1, word2, queue, dic, words))
            break;
        queue.dequeue();
    }
    if(queue.isEmpty())
        cout << "No word ladder found from "<< word2 <<" back to "<< word1 <<".\n" <<endl;
}

bool neighbor(const string &word1, const string &word2, Queue<Stack<string> > &queue, const Lexicon dic, Lexicon &words) {
    string newWord;
    Stack<string> copyStack;
    Stack<string> currentStack = queue.front();
    for(int i = 0; i < (int)currentStack.peek().length(); i++) {
        newWord = currentStack.peek();
        for(int j = 'a'; j < 'z' + 1; j++) {       //try all values A-Z
            newWord[i] = (char) j;                 //form a new word by index
            if(dic.contains(newWord)) {            //if the new word is in the dictionary
                if(newWord == word2) {             //Hooray!
                    currentStack.push(newWord);
                    popStack(currentStack, word1, word2); //pop current stack
                    return true;
                }
                else if(!words.contains(newWord)) {//if the new word never been checked
                    words.add(newWord);            //track new words in dictionary "words"
                    copyStack = currentStack;
                    copyStack.push(newWord);
                    queue.enqueue(copyStack);
                }
            }
        }
    }
    return false;
}

void popStack(Stack<string>& stack, const string& word1, const string& word2) {
    string output;
    while(!stack.isEmpty()) {
        output += stack.pop() += ' ';
    }
    cout << "A ladder from " << word2 <<" back to " << word1 << ":" << endl;
    cout << output << endl << endl;

}
