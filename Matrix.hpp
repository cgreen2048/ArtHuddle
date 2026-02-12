#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include "vec3.hpp"
#include <iostream>
#include <string>
#include <cmath>
#define MATRIX_MAX 3

class Matrix {
    private:
        float components[MATRIX_MAX][MATRIX_MAX];
        vec3 operator[](int);
    
    public:
        Matrix();    
        Matrix(float[MATRIX_MAX][MATRIX_MAX]);
        Matrix(const Matrix&);
        Matrix& operator=(const Matrix&);
        bool operator==(Matrix);
        bool operator!=(Matrix);
        Matrix operator*(Matrix);
        Matrix transpose();
};

#endif