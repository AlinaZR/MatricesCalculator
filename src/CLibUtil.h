//
// Created by Alina Zarubaeva on 15.04.2022.
//

#ifndef MATRIX_CLIBUTIL_H
#define MATRIX_CLIBUTIL_H

#include <iostream>
#include "CMatrix.h"

using namespace std;

/**
 * Helping function to fill matrix from user input
 * @param [in] height Matrix height (number of rows)
 * @param [in] width Matrix width (number of columns)
 * @return Poiner to result matrix
 * @throw invalid_argument If data to insert to matrix
 * are incorrect
 */
CMatrix *fillMatrix(size_t height, size_t width);

/**
 * Helping function to detect sparse matrix
 * @param [in] values All elements from the matrix
 * @return True if matrix is sparse else false
 */
bool isMatrixSparse(vector< vector<double> > &values);

/**
 * Helping function to create sparse or dense matrix
 * @param [in] height Matrix height (number of rows)
 * @param [in] width Matrix width (number of columns)
 * @param [in] values Fill (all elements) of the matrix
 * @return Poiner to result matrix
 */
CMatrix *createMatrix(size_t height, size_t width, vector< vector<double> > values);

#endif //MATRIX_CLIBUTIL_H
