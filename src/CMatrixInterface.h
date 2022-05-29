//
// Created by Alina Zarubaeva on 27.03.2022.
//
#include "CMatrix.h"
#include "CCommand.h"
#include <map>
#include <string>

#ifndef MATRIX_MATRIXINTERFACE_H
#define MATRIX_MATRIXINTERFACE_H

/**
 * Class to create channel for communication with user
 */
class CMatrixInterface {
private:
    ///Name and saved matrix
    map<string, CMatrix *> saved;
    map<string, CCommand *> commands;
    /// Pointer to the last result matrix
    /// to give user chance to save it
    CMatrix *lastCountedMatrix = nullptr;
public:
    /**
     * Default constructor
     */
    CMatrixInterface();

    /**
     * Default destructor
     */
    ~CMatrixInterface();

    /**
     * Disabled copy constructor
     */
    CMatrixInterface(const CMatrixInterface&) = delete;

    /**
     * Disabled assignment operator
     */
    CMatrixInterface& operator=(CMatrixInterface&) = delete;

    /**
     * Method creating interface definition
     * to communicate with user
     */
    void usersProcess();
};

#endif //MATRIX_MATRIXINTERFACE_H
