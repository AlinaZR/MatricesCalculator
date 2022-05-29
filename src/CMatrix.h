//
// Created by Alina Zarubaeva on 27.03.2022.
//

#ifndef MATRIX_CMATRIX_H
#define MATRIX_CMATRIX_H

#include <vector>

using namespace std;

/**
 * Parent class to classes CDenseMatrix and CSparseMatrix
 * to save data about all types of matrices
 */
class CMatrix {
public:
    /**
     * Default constructor for CMatrix class
     */
    CMatrix() = default;

    /**
     * Constructor to create matrix by matrix height and width
     * @param [in] height Height (rows) of matrix
     * @param [in] width Width (columns) of matrix
     */
    CMatrix(size_t height, size_t width);

    /**
     * Default destructor
     */
    virtual ~CMatrix() = default;

    /**
     * Overloaded addition operator to sum one matrix with other
     * @param [in] m Matrix to add
     * @return Pointer to result matrix
     * @throw invalid_argument If dimensions of matrices are different
     */
    CMatrix *operator+(const CMatrix &m) const;

    /**
     * Overloaded minus operator to subtract one matrix from other
     * @param [in] m Matrix to subtract
     * @return Pointer to result matrix
     * @throw invalid_argument If dimensions of matrices are different
     */
    CMatrix *operator-(const CMatrix &m) const;

    /**
     * Overloaded multiplication operator to multiply one matrix by another
     * @param [in] m Matrix to multiply by
     * @return Pointer to result matrix
     * @throw invalid_argument If first matrix has different number of rows
     * from number of columns of second matrix
     */
    CMatrix *operator*(const CMatrix &m) const;

    /**
     * Overloaded multiplication operator to multiply one matrix by a number
     * @param [in] number Number to multiply by
     * @return Pointer to result matrix
     */
    CMatrix *operator*(double number) const;

    /**
     * Overloaded assignment operator to copy matrix
     * @param [in] m Matrix to copy
     * @return Reference to result matrix
     */
    virtual CMatrix &operator=(const CMatrix &m) = 0;

    /**
     * Method to make Gauss elimination on matrix
     * @param [in,out] swapsCounter Variable to count
     * number of swaps of rows while gem
     * @return Pointer to result matrix
     */
    CMatrix *gem(size_t &swapsCounter) const;

    /**
     * Method to make transposition of matrix
     * @return Pointer to result matrix
     */
    virtual CMatrix *transpose() const = 0;

    /**
     * Method to merge one matrix to another with direction
     * @param [in] m Matrix to merge with this
     * @param [in] direction Direction to merge (row/column)
     * @throw invalid_argument If number of rows (if merging to row)
     * or columns (if merging to column) are different
     */
    CMatrix *merge(const CMatrix &m, const string &direction) const;

    /**
     * Method to split matrix to smaller
     * @param [in] cutHeight Height (rows) of new matrix
     * @param [in] cutWidth Width (columns) of new matrix
     * @param [in] fromHeight Height coodrdinate to cut from
     * @param [in] fromWidth Width coodrdinate to cut from
     * @return Pointer to result (splitted) matrix
     * @throw invalid_argument If split conditions are not correct
     * (wrong new matrix dimension, wrong coordinate to split from)
     */
    virtual CMatrix *split(size_t cutHeight, size_t cutWidth, size_t fromHeight,
                           size_t fromWidth) const = 0;

    /**
     * Helping method to get matrix element by row and column coordinates
     * @param [in] heightCoord Height (row) coordinate of element
     * @param [in] widthCoord Width (column) coordinate of element
     * @return Value of matrix element
     */
    virtual double getElem(size_t heightCoord, size_t widthCoord) const = 0;

    /**
     * Helping method to get height (number of rows) of matrix
     */
    size_t getHeight() const;

    /**
     * Helping method to get width (number of columns) of matrix
     */
    size_t getWidth() const;

    /**
     * Method to find determinant of the matrix
     * @return Number representing determinant
     * @throw invalid_argument If matrix is not square
     */
    double determinant() const;

    /**
     * Method to find rank of the matrix
     * @return Number representing rank
     */
    size_t rank() const;

    /**
     * Method making inverse of the matrix
     * @return Poiner to result (inverse) matrix
     * @throw invalid_argument If matrix is not square
     * or determinant is zero
     */
    CMatrix *inverse() const;

    /**
     * Helping function to print the matrix to user output
     */
    void print() const;

    /**
     * Helping function to get fill (all elements) of the matrix
     * @return Vector of vectors containing elements of the matrix
     */
    virtual vector< vector<double> > getData() const = 0;

protected:
    /// Height of the matrix
    size_t height;
    /// Width of the matrix
    size_t width;
    /// Flag to define square matrix
    bool isSquare;
};

#endif //MATRIX_CMATRIX_H
