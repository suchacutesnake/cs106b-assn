// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "lexicon.h"
#include "bogglegui.h"
#include "Boggle.h"
#include "simpio.h"

void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    BoggleGUI::initialize(4, 4);
    string boardText = "";
    if(!getYesOrNo("Do you want to generate a random board?")) {
        boardText = getLine("Type the 16 letters to appear on the board:");
        while(boardText.size() != 16) {
            boardText = getLine("That is not a valid 16-letter board string. Try again.\n"
                                "Type the 16 letters to appear on the board:");
        }
    }
    Boggle boggle(dictionary, boardText);
    string status = "It's your turn!", word;
    boggle.printStatus(status);
    while(true) { //Human's turn
        word = getLine("Type a word (or Enter to stop): ");
        if(word.empty())
            break;
        if(boggle.checkWord(word)) {
            if(!boggle.humanWordSearch(word)) {
                status = "That word can't be formed on this board.";
                boggle.printStatus(status);
            } else {
                status = "You found a new word! ";
                boggle.printStatus(status + '\"' + toUpperCase(word) + '\"');
            }
        }
    }
    //Computer's turn
    cout << endl << "It's my turn!" << endl;
    string computerWords = boggle.computerWordSearch().toString();
    cout << "My words: (" << boggle.getCountComputer() << "): " << computerWords << endl
         << "My score: " << boggle.getScoreComputer() << endl;
    BoggleGUI::setScore(boggle.getScoreComputer(), BoggleGUI::COMPUTER);
    if(boggle.getScoreHuman() >= boggle.getScoreComputer()) {
        cout << "WOW, you defeated me! Congratulations!" << endl;
        BoggleGUI::setStatusMessage("WOW, you defeated me! Congratulations!");
    } else {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
        BoggleGUI::setStatusMessage("Ha ha ha, I destroyed you. Better luck next time, puny human!");
    }
}
