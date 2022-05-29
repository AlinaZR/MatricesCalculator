//
// Created by Alina Zarubaeva on 27.03.2022.
//

#include <vector>
#include <map>
#include "CMatrix.h"

#ifndef MATRIX_SPARSEMATRIX_H
#define MATRIX_SPARSEMATRIX_H

/**
 * Child class to class CMatrix to represent sparse matrices
 */
class CSparseMatrix : public CMatrix {
private:
    /// Map containing pair representing coordinates
    /// of element and double element
    map<pair<int, int>, double> coordAndData;
public:
    /**
     * Constructor to create sparse matrix with defined height,
     * width and elements in it
     * @param [in] height Height (number of rows) of the matrix
     * @param [in] width Width (number of columns) of the matrix
     * @param [in] matrix Fill (all elements) of the matrix
     */
    CSparseMatrix(size_t height, size_t width, vector< vector<double> > &matrix);

    /**
     * Constructor to create sparse matrix with defined height,
     * width and elements in it
     * @param [in] height Height (number of rows) of the matrix
     * @param [in] width Width (number of columns) of the matrix
     * @param [in] data Map containing pair (coordinates)
     * and value of matrix element on this coordinates
     */
    CSparseMatrix(size_t height, size_t width, map<pair<int, int>, double> data);

    ~CSparseMatrix() override = default;

    CMatrix &operator=(const CMatrix &m) override;

    CMatrix *transpose() const override;

    CMatrix *split(size_t cutHeight, size_t cutWidth, size_t fromHeight,
                   size_t fromWidth) const override;

    double getElem(size_t heightCoord, size_t widthCoord) const override;

    vector< vector<double> > getData() const override;
};

#endif //MATRIX_SPARSEMATRIX_H
