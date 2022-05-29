//
// Created by Alina Zarubaeva on 03.05.2022.
//
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <sstream>
#include "CMatrix.h"
#include "CLibUtil.h"

#ifndef MATRIX_CCOMMAND_H
#define MATRIX_CCOMMAND_H

/**
 * Abstract class for implementation of commands call
 * @param[in, out] word First word from user input for command
 * @param[in, out] istream Input string stream with user input
 * @param[in, out] saved Database of saved matrices
 * @param[in, out] lastCountedMatrix Last result matrix for using save command
 */
class CCommand {
public:
    /**
     * Default constructor
     */
    CCommand() = default;

    /**
     * Default destructor
     */
    virtual ~CCommand() = default;

    /**
    * Method to get output and call some function
    * to work with matrix and give user the answer by output
    */
    virtual void callCommand(string &word, istringstream &istream,
                             map<string, CMatrix *> &saved,
                             CMatrix *&lastCountedMatrix) = 0;
};

/**
 * Class for quick call of fill command
 */
class CFill : public CCommand {
public:
    /**
     * Default constructor
     */
    CFill() = default;

    /**
     * Default destructor
     */
    ~CFill() override = default;

    /**
    * Method to get output and call function
    * to fill matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of save command
 */
class CSave : public CCommand {
public:
    /**
     * Default constructor
     */
    CSave() = default;

    /**
     * Default destructor
     */
    ~CSave() override = default;

    /**
    * Method to get output and call function
    * to save matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};


/**
 * Class for quick call of print command
 */
class CPrint : public CCommand {
public:
    /**
     * Default constructor
     */
    CPrint() = default;

    /**
     * Default destructor
     */
    ~CPrint() override = default;

    /**
    * Method to get output and call function
    * to print matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of inverse finding command
 */
class CInverse : public CCommand {
public:
    /**
     * Default constructor
     */
    CInverse() = default;

    /**
     * Default destructor
     */
    ~CInverse() override = default;

    /**
    * Method to get output and call function
    * to get inverse matrix to matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of rank finding command
 */
class CRank : public CCommand {
public:
    /**
     * Default constructor
     */
    CRank() = default;

    /**
     * Default destructor
     */
    ~CRank() override = default;

    /**
    * Method to get output and call function
    * to get rank of matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of gem finding command
 */
class CGem : public CCommand {
public:
    /**
     * Default constructor
     */
    CGem() = default;

    /**
     * Default destructor
     */
    ~CGem() override = default;

    /**
    * Method to get output and call function
    * to do Gauss elimination on matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of determinant finding command
 */
class CDeterminant : public CCommand {
public:
    /**
     * Default constructor
     */
    CDeterminant() = default;

    /**
     * Default destructor
     */
    ~CDeterminant() override = default;

    /**
    * Method to get output and call function
    * to find determinant for matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of two matrices merge command
 */
class CMerge : public CCommand {
public:
    /**
     * Default constructor
     */
    CMerge() = default;

    /**
     * Default destructor
     */
    ~CMerge() override = default;

    /**
    * Method to get output and call function
    * to merge matrixes
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of matrix split command
 */
class CSplit : public CCommand {
public:
    /**
     * Default constructor
     */
    CSplit() = default;

    /**
     * Default destructor
     */
    ~CSplit() override = default;

    /**
    * Method to get output and call function
    * to split matrix to smaller
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of matrix transpose command
 */
class CTranspose : public CCommand {
public:
    /**
     * Default constructor
     */
    CTranspose() = default;

    /**
     * Default destructor
     */
    ~CTranspose() override = default;

    /**
    * Method to get output and call function
    * to transpose the matrix
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call of command without keyword at start
 */
class CNoKeyword : public CCommand {
public:
    /**
     * Default constructor
     */
    CNoKeyword() = default;

    /**
     * Default destructor
     */
    ~CNoKeyword() override = default;

    /**
    * Method to get output and call function
    * to to command without keyword on matrix
     * (+, =, -, *, create new matrix)
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

/**
 * Class for quick call help command to show instructions to user
 */
class CHelp : public CCommand {
public:
    /**
     * Default constructor
     */
    CHelp() = default;

    /**
     * Default destructor
     */
    ~CHelp() override = default;

    /**
    * Method to show instruction to program to user
    */
    void callCommand(string &word, istringstream &istream,
                     map<string, CMatrix *> &saved,
                     CMatrix *&lastCountedMatrix) override;
};

#endif //MATRIX_CCOMMAND_H
