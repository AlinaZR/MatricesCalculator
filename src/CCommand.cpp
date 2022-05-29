//
// Created by Alina Zarubaeva on 03.05.2022.
//
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <fstream>
#include "CMatrix.h"
#include "CLibUtil.h"
#include "CCommand.h"

using namespace std;

void CFill::callCommand(string &word, istringstream &istream,
                        map<string, CMatrix *> &saved,
                        CMatrix *&lastCountedMatrix) {
    if (istream >> skipws >> word) {
        auto matrix = saved.find(word);
        if (matrix != saved.end()) {
            *(matrix->second) = *(fillMatrix(matrix->second->getHeight(),
                                             matrix->second->getWidth()));
        } else {
            cout << "Matrix named '" << word
                 << "' doesn't exist. Please, try again." << endl << endl;
        }
    } else {
        cout << "Command has been written wrong. Please try again" << endl
             << endl;
    }
}

void CSave::callCommand(string &word, istringstream &istream,
                        map<string, CMatrix *> &saved,
                        CMatrix *&lastCountedMatrix) {
    if (lastCountedMatrix == nullptr) {
        cout
                << "No matrix saved in a buffer. Please, make some operations and try again."
                << endl;
        return;
    }
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        saved.insert({word, createMatrix(lastCountedMatrix->getHeight(),
                                         lastCountedMatrix->getWidth(),
                                         lastCountedMatrix->getData())});
        cout << "Matrix '" << word << "' has been successfully saved" << endl;
    } else {
        cout << "Matrix named '" << word << "' has been already created.\n"
                                            "Do you want to rewrite data?(write letter 'y' "
                                            "if yes, else 'n' or others)"
             << endl;
        string userInput;
        char ans;
        getline(cin, userInput);
        istringstream iss(userInput);
        iss >> skipws >> ans;
        toupper(ans);
        if (ans == 'Y') {
            *mat->second = *lastCountedMatrix;
            cout << "Matrix'" << word << "'has been successfully filled"
                 << endl;
        } else {
            cout << "Ok, no changes has been applied." << endl;
        }
    }
}

void CPrint::callCommand(string &word, istringstream &istream,
                         map<string, CMatrix *> &saved,
                         CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word
             << "' doesn't exist. Please, try again." << endl << endl;
    } else {
        mat->second->print();
    }
}

void CInverse::callCommand(string &word, istringstream &istream,
                           map<string, CMatrix *> &saved,
                           CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word
             << "' doesn't exist. Please, try again." << endl << endl;
    } else {
        try {
            delete lastCountedMatrix;
            lastCountedMatrix = createMatrix(mat->second->getHeight(),
                                             mat->second->getWidth(),
                                             (mat->second->inverse())->getData());
            lastCountedMatrix->print();
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
}

void CRank::callCommand(string &word, istringstream &istream,
                        map<string, CMatrix *> &saved,
                        CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word
             << "' doesn't exist. Please, try again." << endl << endl;
    } else {
        cout << "Rank of matrix is " << mat->second->rank() << endl;
    }
}

void CGem::callCommand(string &word, istringstream &istream,
                       map<string, CMatrix *> &saved,
                       CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word
             << "' doesn't exist. Please, try again." << endl << endl;
    } else {
        size_t gemSwapsCount = 0;
        delete lastCountedMatrix;
        lastCountedMatrix = createMatrix(mat->second->getHeight(),
                                         mat->second->getWidth(),
                                         (mat->second->gem(
                                                 gemSwapsCount))->getData());
        lastCountedMatrix->print();
    }
}

void CDeterminant::callCommand(string &word, istringstream &istream,
                               map<string, CMatrix *> &saved,
                               CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word
             << "' doesn't exist. Please, try again." << endl << endl;
    } else {
        try {
            cout << "Matrix determinant is " << mat->second->determinant()
                 << endl;
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
}

void CMerge::callCommand(string &word, istringstream &istream,
                         map<string, CMatrix *> &saved,
                         CMatrix *&lastCountedMatrix) {
    string matstr1, matstr2;
    if (istream >> skipws >> matstr1 && istream >> skipws >> matstr2) {
        auto mat1 = saved.find(matstr1);
        auto mat2 = saved.find(matstr2);
        if (mat1 != saved.end() && mat2 != saved.end()) {
            istream >> skipws >> word;
            if (word == "COLUMN" || word == "ROW") {
                try {
                    delete lastCountedMatrix;
                    lastCountedMatrix = mat1->second->merge(*(mat2->second),
                                                            word);
                    lastCountedMatrix->print();
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
            } else {
                cout << "Direction is written wrong or empty. "
                        "Please, try again." << endl;
            }
        } else {
            cout << "One (or two) matrix with "
                    "this names doesn't exist. Please, try again." << endl;
        }
    } else {
        cout << "Wrong argument number. Please, try again." << endl;
    }
}


void CSplit::callCommand(string &word, istringstream &istream,
                         map<string, CMatrix *> &saved,
                         CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word << "' doesn't exist. "
                                            "Please, try again.\n" << endl;
    } else {
        char bufChar = ' ';
        size_t cutH, cutW, fromH, fromW;
        if (istream >> skipws >> bufChar && bufChar == '[' &&
            istream >> skipws >> cutH &&
            istream >> skipws >> bufChar && bufChar == ']' &&
            istream >> skipws >> bufChar && bufChar == '[' &&
            istream >> skipws >> cutW &&
            istream >> skipws >> bufChar && bufChar == ']' &&
            istream >> skipws >> bufChar && bufChar == '(' &&
            istream >> skipws >> fromH &&
            istream >> skipws >> bufChar && bufChar == ',' &&
            istream >> skipws >> fromW &&
            istream >> skipws >> bufChar && bufChar == ')') {
            try {
                delete lastCountedMatrix;
                lastCountedMatrix = createMatrix(
                        cutH, cutW, mat->second->split(
                                cutH, cutW, fromH, fromW)->getData());
                lastCountedMatrix->print();
            } catch (exception &e) {
                cout << e.what() << endl;
            }
        } else {
            cout << "Command has been written wrong. Please, try again."
                 << endl;
        }
    }
}

void CTranspose::callCommand(string &word, istringstream &istream,
                             map<string, CMatrix *> &saved,
                             CMatrix *&lastCountedMatrix) {
    istream >> skipws >> word;
    auto mat = saved.find(word);
    if (mat == saved.end()) {
        cout << "Matrix named '" << word
             << "' doesn't exist. Please, try again." << endl << endl;
    } else {
        delete lastCountedMatrix;
        lastCountedMatrix = mat->second->transpose();
        lastCountedMatrix->print();
    }
}

void CNoKeyword::callCommand(string &word, istringstream &istream,
                             map<string, CMatrix *> &saved,
                             CMatrix *&lastCountedMatrix) {
    auto mat1 = saved.find(word);
    char bufChar1 = ' ', bufChar2, bufChar3, bufChar4;
    string wordTwo;
    size_t bufNumber1, bufNumber2;
    if (mat1 == saved.end()) {
        if (istream >> skipws >> bufChar1 && bufChar1 == '[' &&
            istream >> skipws >> bufNumber1 &&
            istream >> skipws >> bufChar2 && bufChar2 == ']' &&
            istream >> skipws >> bufChar3 &&
            bufChar3 == '[' && istream >> skipws >> bufNumber2 &&
            istream >> skipws >> bufChar4 && bufChar4 == ']') {
            try {
                saved.insert({word, fillMatrix(bufNumber1, bufNumber2)});
                return;
            } catch (exception &e) {
                cout << e.what() << endl;
                return;
            }
        } else {
            cout << "Matrix named '" << word <<
                 "' doesn't exist.\nOperation has been "
                 "written wrong. Please, try again." << endl;
        }
    } else if (istream >> skipws >> bufChar1 &&
               (bufChar1 == '+' || bufChar1 == '-' || bufChar1 == '*' ||
                bufChar1 == '=') &&
               istream >> skipws >> wordTwo) {
        auto mat2 = saved.find(wordTwo);
        if (mat2 != saved.end()) {
            try {
                if (bufChar1 == '+') {
                    delete lastCountedMatrix;
                    lastCountedMatrix = createMatrix(
                            mat1->second->getHeight(),
                            mat1->second->getWidth(),
                            (*(mat1->second) +
                             *(mat2->second))->getData());
                } else if (bufChar1 == '-') {
                    delete lastCountedMatrix;
                    lastCountedMatrix = createMatrix(
                            mat1->second->getHeight(),
                            mat1->second->getWidth(),
                            (*(mat1->second) -
                             *(mat2->second))->getData());
                } else if (bufChar1 == '*') {
                    delete lastCountedMatrix;
                    lastCountedMatrix = createMatrix(
                            mat1->second->getHeight(),
                            mat2->second->getWidth(),
                            (*(mat1->second) *
                             *(mat2->second))->getData());
                } else {
                    if (mat1 == mat2) {
                        cout << "Matrix tries to copy herself. Operation skipped." << endl;
                        return;
                    }
                    delete lastCountedMatrix;
                    lastCountedMatrix = createMatrix(
                            mat2->second->getHeight(),
                            mat2->second->getWidth(),
                            (*(mat1->second) = *(mat2->second)).getData());
                }
                lastCountedMatrix->print();
            } catch (exception &e) {
                cout << e.what() << endl;
            }
        } else if (bufChar1 == '*') {
            stringstream numSS(wordTwo);
            double toMultiply;
            if (numSS >> toMultiply) {
                delete lastCountedMatrix;
                lastCountedMatrix = createMatrix(mat1->second->getHeight(),
                                                 mat1->second->getWidth(),
                                                 (*(mat1->second) *
                                                  toMultiply)->getData());
                lastCountedMatrix->print();
            } else {
                cout
                        << "Second argument for multiplying matrix is wrong. Please, try again."
                        << endl;
            }
        }
    } else {
        cout << "Command has been written wrong. Please, try again."
             << endl;
    }
}

void CHelp::callCommand(string &word, istringstream &istream,
        map<string, CMatrix *> &saved,
        CMatrix *&lastCountedMatrix){
    string out;
    ifstream fInput;
    fInput.open("/Users/alina.zarubaeva/CLionProjects/zarubal1/Matrix/src/InterfaceTexts/available_operations");
    if (fInput.is_open()) {
        while (getline(fInput, out))
            cout << out << "\n";
        fInput.clear();
        fInput.seekg(0, ios::beg);
    }
}

