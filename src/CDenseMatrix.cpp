//
// Created by Alina Zarubaeva on 27.03.2022.
//

#include "CDenseMatrix.h"
#include "CLibUtil.h"

CDenseMatrix::CDenseMatrix(size_t height, size_t width,
                           vector< vector<double> > &matrix) : CMatrix(height,
                                                                     width) {
    for (size_t h = 0; h < height; h++) {
        vector<double> row;
        data.emplace_back(row);
        for (size_t w = 0; w < width; w++) {
            data[h].emplace_back(matrix[h][w]);
        }
    }
}

CMatrix &CDenseMatrix::operator=(const CMatrix &m) {
    height = m.getHeight();
    width = m.getWidth();
    isSquare = height == width;
    data.clear();
    data.resize(height);
    for (size_t h = 0; h < height; ++h) {
        for (size_t w = 0; w < width; ++w) {
            data[h].emplace_back(m.getElem(h, w));
        }
    }
    return *this;
}

CMatrix *CDenseMatrix::transpose() const {
    vector< vector<double> > newFilling;
    for (size_t w = 0; w < width; w++) {
        vector<double> newRow;
        newFilling.emplace_back(newRow);
        for (size_t h = 0; h < height; h++) {
            newFilling[w].emplace_back(data[h][w]);
        }
    }
    return new CDenseMatrix(width, height, newFilling);
}

CMatrix *
CDenseMatrix::split(size_t cutHeight, size_t cutWidth, size_t fromHeight,
                    size_t fromWidth) const {
    if (cutHeight + fromHeight > height || cutWidth + fromWidth > width) {
        throw invalid_argument("Coordinates are wrong. Please, try again.");
    }
    vector< vector<double> > newFilling;
    fromHeight--, fromWidth--;
    newFilling.resize(cutHeight);
    for (size_t h = fromHeight; h < fromHeight + cutHeight; h++) {
        for (size_t w = fromWidth; w < fromWidth + cutWidth; w++) {
            newFilling[h - fromHeight].emplace_back(data[h][w]);
        }
    }
    return createMatrix(cutHeight, cutWidth, newFilling);
}

double CDenseMatrix::getElem(size_t heightCoord, size_t widthCoord) const {
    return data[heightCoord][widthCoord];
}

vector< vector<double> > CDenseMatrix::getData() const {
    return data;
}
