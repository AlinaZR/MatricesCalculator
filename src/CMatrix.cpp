//
// Created by Alina Zarubaeva on 27.03.2022.
//

#include <iomanip>
#include <cmath>
#include "CMatrix.h"
#include "CLibUtil.h"
#include "CDenseMatrix.h"

using namespace std;

CMatrix::CMatrix(size_t h, size_t w) {
    height = h;
    width = w;
    isSquare = (height == width);
}

CMatrix *CMatrix::operator+(const CMatrix &m) const {
    if (this->height != m.height || this->width != m.width) {
        throw invalid_argument("Matrix size is not same. "
                               "Addition and subtraction "
                               "operations is not available.");
    }
    vector< vector<double> > newFilling;
    for (size_t h = 0; h < this->height; h++) {
        vector<double> newRow;
        newFilling.emplace_back(newRow);
        for (size_t w = 0; w < this->width; w++) {
            newFilling[h].emplace_back(this->getElem(h, w) + m.getElem(h, w));
        }
    }
    return createMatrix(this->height, this->width, newFilling);
}

CMatrix *CMatrix::operator-(const CMatrix &m) const {
    return *this + *(m * (-1));
}

CMatrix *CMatrix::operator*(const CMatrix &m) const {
    if (this->width != m.height) {
        throw invalid_argument("First matrix must have same height "
                               "as width of second matrix. "
                               "Multiplication is not available.");
    }
    size_t newHeight = this->height;
    size_t newWidth = m.width;
    vector< vector<double> > newFilling;
    newFilling.resize(newHeight);
    for (size_t h = 0; h < newHeight; h++) {
        for (size_t w = 0; w < newWidth; w++) {
            double res = 0;
            for (size_t i = 0; i < width; i++) {
                res += this->getElem(h, i) * m.getElem(i, w);
            }
            newFilling[h].emplace_back(res > 0.0000001 ? res : 0);
        }
    }
    return createMatrix(newHeight, newWidth, newFilling);
}

CMatrix *CMatrix::operator*(double number) const {
    vector< vector<double> > newFilling;
    for (size_t h = 0; h < height; h++) {
        vector<double> newRow;
        newFilling.emplace_back(newRow);
        for (size_t w = 0; w < width; w++) {
            newFilling[h].emplace_back(getElem(h, w) * number);
        }
    }
    return createMatrix(height, width, newFilling);
}

size_t CMatrix::getHeight() const {
    return height;
}

size_t CMatrix::getWidth() const {
    return width;
}

CMatrix *CMatrix::gem(size_t &swapsCounter) const {
    vector< vector<double> > matrix = getData();
    for (size_t h = 0; h < height; h++) {
        // Way to find maximum in this column
        double maxEl = fabs(matrix[h][h]); // element from diagonal without sign
        size_t maxRow = h;
        for (size_t hcmp = h + 1; hcmp < height; hcmp++) {
            if (fabs(matrix[hcmp][h]) > maxEl) {
                maxEl = fabs(matrix[hcmp][h]);
                maxRow = hcmp;
            }
        }
        if (maxRow != h){
            swapsCounter ++;
            for (size_t w = h; w < width; w++) {
                double temp =
                        fabs(matrix[maxRow][w]) > 0.0000001 ? matrix[maxRow][w] : 0;
                matrix[maxRow][w] =
                        fabs(matrix[h][w]) > 0.0000001 ? matrix[h][w] : 0;
                matrix[h][w] = temp;
            }
        }
        for (size_t hcmp = h + 1; hcmp < height; hcmp++) {
            double c = -matrix[hcmp][h] / matrix[h][h];
            if (matrix[h][h] == 0 || c != c) {
                c = 0;
            }
            for (size_t w = h; w < width; w++) {
                if (h != w) {
                    matrix[hcmp][w] += c * matrix[h][w];
                    matrix[hcmp][w] =
                            fabs(matrix[hcmp][w]) > 0.0000001 ? matrix[hcmp][w]
                                                              : 0;
                } else {
                    matrix[hcmp][w] = 0;
                }
            }
        }
    }
    return createMatrix(height, width, matrix);
}

CMatrix *CMatrix::merge(const CMatrix &m, const string &direction) const {
    size_t newHeight = height;
    size_t newWidth = width;
    vector< vector<double> > newFilling;
    newFilling.resize(height);
    for (size_t h = 0; h < height; h++) {
        for (size_t w = 0; w < width; w++) {
            newFilling[h].emplace_back(getElem(h, w));
        }
    }
    if (direction == "COLUMN") {
        if (width != m.width) {
            throw invalid_argument("Matrices width sizes are not same. "
                                   "Merge operation is not available.");
        }
        newHeight += m.height;
        newFilling.resize(newHeight);
        for (size_t h = 0; h < m.height; h++) {
            for (size_t w = 0; w < m.width; w++) {
                newFilling[h + height].emplace_back(m.getElem(h, w));
            }
        }
        return createMatrix(newHeight, newWidth, newFilling);
    } else if (direction == "ROW") {
        if (height != m.height) {
            throw invalid_argument("Matrices height sizes are not same. "
                                   "Merge operation is not available.");
        }
        newWidth += m.width;
        for (size_t h = 0; h < m.height; ++h) {
            for (size_t w = 0; w < m.width; w++) {
                newFilling[h].emplace_back(m.getElem(h, w));
            }
        }
    }
    return createMatrix(newHeight, newWidth, newFilling);
}

double CMatrix::determinant() const {
    if (!isSquare) {
        throw invalid_argument("Matrix is not square."
                               "Determinant finding operation is not available");
    }
    size_t gemSwapsCount = 0;
    CMatrix *cp = gem(gemSwapsCount);
    double d = 1;
    for (size_t h = 0; h < height; h++) {
        d *= cp->getElem(h, h); //diagonal elements multiplying
    }
    return d * pow(-1, gemSwapsCount);
}

size_t CMatrix::rank() const {
    size_t gemSwapsCount = 0;
    CMatrix *cp = gem(gemSwapsCount);
    size_t r = height;
    for (size_t h = 0; h < height; ++h) {
        size_t w = 0;
        while (w < width) {
            if (cp->getElem(h, w) != 0) break;
            w++;
        }
        if (w == width) r--;
    }
    return r;
}

CMatrix *CMatrix::inverse() const {
    if (!isSquare)
        throw invalid_argument(
                "Unable to find inverse matrix for this - matrix is not square.");
    size_t gemSwapsCount = 0;
    double d = determinant();
    if (d == 0)
        throw invalid_argument(
                "Unable to find inverse matrix for this (determinant is zero).");
    vector< vector<double> > determMatrixValues;
    determMatrixValues.resize(height);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            vector< vector<double> > detWithoutOne;
            detWithoutOne.resize(height - 1);
            for (size_t h = 0; h < height; h++) {
                for (size_t w = 0; w < width; w++) {
                    if (h != i && w != j) {
                        size_t addToPlace = h > i ? h - 1 : h;
                        detWithoutOne[addToPlace].emplace_back(
                                this->getElem(h, w));
                    }
                }
            }
            CMatrix *matrixForDeterm = createMatrix(height - 1, width - 1,
                                                    detWithoutOne);
            determMatrixValues[i].emplace_back(
                    matrixForDeterm->determinant() * pow(-1, i + j) * (1 / d));
            delete matrixForDeterm;
        }
    }
    CMatrix *determMatrixTransposed = createMatrix(height, width,
                                                   determMatrixValues)->transpose();
    return determMatrixTransposed;
}

void CMatrix::print() const {
    cout << "Result is:" << endl;
    for (size_t h = 0; h < height; ++h) {
        for (size_t w = 0; w < width; ++w) {
            cout << setw(6) << getElem(h, w) << " ";
        }
        cout << endl;
    }
}

