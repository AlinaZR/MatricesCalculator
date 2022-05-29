//
// Created by Alina Zarubaeva on 27.03.2022.
//
#include <vector>
#include "CMatrix.h"

#ifndef MATRIX_DENSEMATRIX_H
#define MATRIX_DENSEMATRIX_H

/**
 * Child class to class CMatrix to represent dense matrices
 */
class CDenseMatrix : public CMatrix {
private:
    /// Parameter for saving fill of the matrix
    /// (all rows and columns values)
    vector< vector<double> > data;
public:
    /**
     * Default constructor
     */
    CDenseMatrix() = default;

    /**
     * Constructor to create sparse matrix with defined height,
     * width and elements in it
     * @param [in] height Height (number of rows) of the matrix
     * @param [in] width Width (number of columns) of the matrix
     * @param [in] matrix Fill (all elements) of the matrix
     */
    CDenseMatrix(size_t height, size_t width, vector< vector<double> > &matrix);

    ~CDenseMatrix() override = default;

    CMatrix &operator=(const CMatrix &m) override;

    CMatrix *transpose() const override;

    CMatrix *split(size_t cutHeight, size_t cutWidth, size_t fromHeight,
                   size_t fromWidth) const override;

    double getElem(size_t heightCoord, size_t widthCoord) const override;

    vector< vector<double> > getData() const override;
};

#endif //MATRIX_DENSEMATRIX_H
