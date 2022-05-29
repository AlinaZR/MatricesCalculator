//
// Created by Alina Zarubaeva on 27.03.2022.
//

#include <iostream>
#include <fstream>
#include "CMatrixInterface.h"

CMatrixInterface::CMatrixInterface() {
    commands.insert(make_pair("FILL", new CFill()));
    commands.insert(make_pair("SAVE", new CSave()));
    commands.insert(make_pair("PRINT", new CPrint()));
    commands.insert(make_pair("INV", new CInverse()));
    commands.insert(make_pair("RANK", new CRank()));
    commands.insert(make_pair("GEM", new CGem()));
    commands.insert(make_pair("DET", new CDeterminant()));
    commands.insert(make_pair("MERGE", new CMerge()));
    commands.insert(make_pair("SPLIT", new CSplit()));
    commands.insert(make_pair("TRANS", new CTranspose()));
    commands.insert(make_pair("NOKEYWORD", new CNoKeyword()));
    commands.insert(make_pair("HELP", new CHelp()));
}

CMatrixInterface::~CMatrixInterface() {
    for (const auto& command : commands){
        delete command.second;
    }
    commands.clear();
}

void CMatrixInterface::usersProcess() {
    cout << "Welcome in CMatrix calculator!" << endl;
    string userInput;
    istringstream nullStream;
    commands["HELP"]->callCommand(userInput, nullStream, saved, lastCountedMatrix);
    do {
        getline(cin, userInput);
        std::for_each(userInput.begin(), userInput.end(), [](char &c) {
            c = ::toupper(c);
        });
        string word;
        istringstream iss(userInput);
        if (!(iss >> skipws >> word)) {
            cout << "Your input is wrong. Please, try again." << endl << endl;
            continue;
        }
        auto call = commands.find(word);
        if (call == commands.end()){
            if (word == "BREAK") {
                cout << "Thank you for using this program! See you later! :)"
                     << endl;
                break;
            } else {
                commands["NOKEYWORD"]->callCommand(word, iss, saved, lastCountedMatrix);
            }
        } else {
            call->second->callCommand(word, iss, saved, lastCountedMatrix);
        }
    } while (true);
}