//
// Created by Alina Zarubaeva on 15.04.2022.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "CLibUtil.h"
#include "CSparseMatrix.h"
#include "CDenseMatrix.h"
#include "CMatrix.h"

bool isMatrixSparse(size_t height, size_t width, vector< vector<double> > &values) {
    size_t zeroes = 0;
    for (size_t h = 0; h < height; h++) {
        for (size_t w = 0; w < width; w++) {
            if (values[h][w] == 0) zeroes++;
        }
    }
    return zeroes > height * width / 2;
}

CMatrix *createMatrix(size_t height, size_t width, vector< vector<double> > values) {
    if (isMatrixSparse(height, width, values)) {
        return new CSparseMatrix(height, width, values);
    } else {
        return new CDenseMatrix(height, width, values);
    }
}

CMatrix *fillMatrix(size_t height, size_t width) {
    double elem;
    vector< vector<double> > filling;
    cout << "Matrix has " << height << " rows and " << width << " columns."
         << endl;
    cout << "Enter the elements of the matrix (all " << height * width
         << " elements to row):" << endl;
    string userInput;
    getline(cin, userInput);
    istringstream iss(userInput);
    for (size_t h = 0; h < height; h++) {
        vector<double> newVector;
        filling.emplace_back(newVector);
        for (size_t w = 0; w < width; w++) {
            if (iss >> skipws >> elem) {
                filling[h].emplace_back(elem);
            } else {
                throw invalid_argument("Wrong data format. Please, try again");
            }
        }
    }
    cout << "Matrix has been successfully filled." << endl;
    return createMatrix(height, width, filling);
}