//
// Created by Alina Zarubaeva on 27.03.2022.
//

#include "CSparseMatrix.h"
#include "CDenseMatrix.h"

using namespace std;

CSparseMatrix::CSparseMatrix(size_t height, size_t width,
                             vector< vector<double> > &matrix) : CMatrix(height,
                                                                      width) {
    for (size_t h = 0; h < height; h++) {
        for (size_t w = 0; w < width; w++) {
            if (matrix[h][w] != 0) {
                coordAndData.insert(make_pair(make_pair(h, w), matrix[h][w]));
            }
        }
    }
}

CSparseMatrix::CSparseMatrix(size_t height, size_t width,
                             map<pair<int, int>, double> data) : CMatrix(height,
                                                                         width) {
    coordAndData = std::move(data);
}

CMatrix &CSparseMatrix::operator=(const CMatrix &m) {
    height = m.getHeight();
    width = m.getWidth();
    isSquare = height == width;
    coordAndData.clear();
    for (size_t h = 0; h < height; ++h) {
        for (size_t w = 0; w < width; ++w) {
            coordAndData.insert(make_pair(make_pair(h, w), m.getElem(h, w)));
        }
    }
    return *this;
}

CMatrix *CSparseMatrix::transpose() const {
    map<pair<int, int>, double> newCoordAndData;
    for (const auto &elem: coordAndData) {
        newCoordAndData.insert(
                make_pair(make_pair(elem.first.second, elem.first.first),
                          elem.second));
    }
    return new CSparseMatrix(width, height, newCoordAndData);
}

CMatrix * CSparseMatrix::split(size_t cutHeight, size_t cutWidth, size_t fromHeight,
                     size_t fromWidth) const {
    if (cutHeight + fromHeight > height || cutWidth + fromWidth > width) {
        throw invalid_argument("Coordinates are wrong. Please, try again.");
    }
    map<pair<int, int>, double> newCoordAndData;
    for (const auto &elem: coordAndData) {
        if (elem.first.first < fromHeight + cutHeight &&
            elem.first.second < fromWidth + cutWidth) {
            newCoordAndData.insert(elem);
        }
    }
    return new CSparseMatrix(height, width, newCoordAndData);
}

double CSparseMatrix::getElem(size_t heightCoord, size_t widthCoord) const {
    auto elem = coordAndData.find(make_pair(heightCoord, widthCoord));
    if (elem == coordAndData.end()) return 0;
    return elem->second;
}

vector< vector<double> > CSparseMatrix::getData() const {
    CDenseMatrix d;
    d = *this;
    return d.getData();
}

