#include "ArtHuddle/core/Matrix.hpp"

// Source file for Matrix header, holds Matrix class implementation

Matrix::Matrix() : components{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} {
    // placeholder
}

Matrix::Matrix(float _data[MATRIX_MAX][MATRIX_MAX]) : Matrix() {
    for (int i = 0; i < MATRIX_MAX; i++) {
        for (int j = 0; j < MATRIX_MAX; j++) {
            components[i][j] = _data[i][j];
        }
    }
}

Matrix::Matrix(const Matrix& cp) : Matrix() {
    for (int i = 0; i < MATRIX_MAX; i++) {
        for (int j = 0; j < MATRIX_MAX; j++) {
            components[i][j] = cp.components[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& cp) {
    if (this == &cp) {
        return *this;
    }
    for (int i = 0; i < MATRIX_MAX; i++) {
        for (int j = 0; j < MATRIX_MAX; j++) {
            components[i][j] = cp.components[i][j];
        }
    }
    return *this;
}

vec3 Matrix::operator[](int i) {    // private method
    int size = sizeof(components)/sizeof(components[0]);
    if ((i < 0) || (i >= size)) {
        std::cerr << "ERROR: ACCESSING MEMORY OUTSIDE OF SCOPE. RETURNING FIRST ROW\n";
        return vec3(components[0][0], components[0][1], components[0][2]);
    }
    vec3 holder = vec3(components[i][0], components[i][1], components[i][2]);
    return holder;
}

bool Matrix::operator==(Matrix rhs) {
    for (int i = 0; i < MATRIX_MAX; i++) {
        for (int j = 0; j < MATRIX_MAX; j++) {
            if (this->components[i][j] != rhs.components[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(Matrix rhs) {
    return !(*this == rhs);
}

Matrix Matrix::operator*(Matrix rhs) {
    vec3 row0 = (*this)[0];
    vec3 row1 = (*this)[1];
    vec3 row2 = (*this)[2];

    vec3 col0 = vec3((*this)[0][0], (*this)[0][1], (*this)[0][2]);
    vec3 col1 = vec3((*this)[1][0], (*this)[1][1], (*this)[1][2]);
    vec3 col2 = vec3((*this)[2][0], (*this)[2][1], (*this)[2][2]);

    float holder[MATRIX_MAX][MATRIX_MAX] = {
        {row0.dot(col0), row0.dot(col1), row0.dot(col2)},
        {row1.dot(col0), row1.dot(col1), row1.dot(col2)},
        {row2.dot(col0), row2.dot(col1), row2.dot(col2)}
    };

    return Matrix(holder);
}

Matrix Matrix::transpose() {
    float holder[MATRIX_MAX][MATRIX_MAX] = {
        {(*this)[0][0], (*this)[1][0], (*this)[2][0]},
        {(*this)[0][1], (*this)[1][1], (*this)[2][1]},
        {(*this)[0][2], (*this)[1][2], (*this)[2][2]}
    };
    return Matrix(holder);
}