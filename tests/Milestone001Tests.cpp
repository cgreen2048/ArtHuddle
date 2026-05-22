#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"
#include "ArtHuddle/core/Matrix.hpp"
#include <iostream>

// Unit tests for vec2, ivec2, vec3, ivec3, Matrix classes

int vec2_tester();
int ivec2_tester();
int vec3_tester();
int ivec3_tester();
int matrix_tester();

int main() {
    int failure = 0;
    if (vec2_tester() || ivec2_tester() || vec3_tester() || ivec3_tester() || matrix_tester()) {
        failure = 1;
    } 
    if (failure) {
        std::cout << "IMPLEMENTATION(S) FAILED, REVIEW TEST RESULTS\n";
    }
    else {
        std::cout << "ALL TESTS PASSED\n";
    }

    return failure;
}


int vec2_tester() {
    std::cout << "***** TESTING VEC2 FUNCTIONALITY *****\n";
    int failure = 0;
    vec2 test = vec2(2.5, 3.5);
    vec2 copy{test};

    if (test != copy) {
        std::cout << "copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "copy constructor working\n";
    }

    vec2 equalsCopy = test;

    if (test != equalsCopy) {
        std::cout << "operator= FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "operator= working\n";
    }

    vec2 expected = vec2(5.0, 7.0);
    vec2 result = test + test;
    if (expected != result) {
        std::cout << "add function FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "add function working\n";
    }

    float scalar = 4.5;
    expected = vec2(11.25, 15.75);
    result = test * scalar;
    if (expected == result) {
        std::cout << "scalar mult function working\n";
    }
    else {
        std::cout << "scalar mult function FAILED!\n";
        failure = 1;
    }

    expected = vec2(0.0, 0.0);
    result = test - test;
    if (expected == result) {
        std::cout << "subtract function working\n";
    }
    else {
        std::cout << "subtract function FAILED!\n";
        failure = 1;
    }

    float expected4 = 18.5;
    float result4 = test.dot(test);
    if (expected4 == result4) {
        std::cout << "dot product function working\n";
    }
    else {
        std::cout << "dot product function FAILED!\n";
        failure = 1;
    }

    float expected5 = std::sqrt(18.5);
    float result5 = test.mag();
    if (expected5 == result5) {
        std::cout << "magnitude function working\n";
    }
    else {
        std::cout << "magnitude product function FAILED!\n";
        failure = 1;
    }

    expected = vec2(2.5/std::sqrt(18.5), 3.5/std::sqrt(18.5));
    result = test.unit();
    if (expected == result) {
        std::cout << "unit vector function working\n";
    }
    else {
        std::cout << "unit vector function FAILED!\n";
        failure = 1;
    }

    float expected6 = 0.0;
    float result6 = test.cross(test);
    if (expected6 == result6) {
        std::cout << "cross product function working\n";
    }
    else {
        std::cout << "cross product function FAILED!\n";
        failure = 1;
    }

    std::cout << "printing vector by using [] operator: (" << test[0] << ", " << test[1] << ")\n";

    test+= test;
    expected = vec2(5.0, 7.0);
    if (expected == test) {
        std::cout << "self-assign add function working\n";
    }
    else {
        std::cout << "self-assign add function FAILED!\n";
        failure = 1;
    }
    
    test*= 4.5;
    expected = vec2(22.5, 31.5);
    if (expected == test) {
        std::cout << "self-assign scalar mult function working\n";
    }
    else {
        std::cout << "self-assign scalar mult function FAILED!\n";
        failure = 1;
    }

    test-= test;
    expected = vec2(0.0, 0.0);
    if (expected == test) {
        std::cout << "self-assign subtract function working\n";
    }
    else {
        std::cout << "self-assign subtract function FAILED!\n";
        failure = 1;
    }

    return failure;
}


int ivec2_tester() {
    std::cout << "***** TESTING IVEC2 FUNCTIONALITY *****\n";    
    int failure = 0;
    ivec2 test = ivec2(2, 3);

    ivec2 expected = ivec2(4, 6);
    ivec2 result = test + test;

    int expected5 = static_cast<int>(std::round(std::sqrt(13)));
    int result5 = test.mag();
    if (expected5 == result5) {
        std::cout << "magnitude function working\n";
    }
    else {
        std::cout << "magnitude product function FAILED!\n";
        failure = 1;
    }
    
    expected = ivec2(static_cast<int>(std::round(2/expected5)), static_cast<int>(std::round(3/expected5)));
    result = test.unit();
    if (expected == result) {
        std::cout << "unit vector function working\n";
    }
    else {
        std::cout << "unit vector function FAILED!\n";
        failure = 1;
    }


    return failure;
}


int vec3_tester() {
    std::cout << "***** TESTING VEC3 FUNCTIONALITY *****\n";    
    int failure = 0;
    vec3 test = vec3(2.5, 3.5, 4.5);
    vec3 copy{test};

    if (test != copy) {
        std::cout << "copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "copy constructor working\n";
    }
    
    vec3 equalsCopy = test;
    if (test != equalsCopy) {
        std::cout << "copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "copy constructor working\n";
    }

    vec3 expected = vec3(5.0, 7.0, 9.0);
    vec3 result = test + test;
    if (expected != result) {
        std::cout << "add function FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "add function working\n";
    }

    float scalar = 3.5;
    expected = vec3(8.75, 12.25, 15.75);
    result = test * scalar;
    if (expected == result) {
        std::cout << "scalar mult function working\n";
    }
    else {
        std::cout << "scalar mult function FAILED!\n";
        failure = 1;
    }

    expected = vec3(0.0, 0.0, 0.0);
    result = test - test;
    if (expected == result) {
        std::cout << "subtract function working\n";
    }
    else {
        std::cout << "subtract function FAILED!\n";
        failure = 1;
    }

    float expected4 = 38.75;
    float result4 = test.dot(test);
    if (expected4 == result4) {
        std::cout << "dot product function working\n";
    }
    else {
        std::cout << "dot product function FAILED!\n";
        failure = 1;
    }

    float expected5 = std::sqrt(38.75);
    float result5 = test.mag();
    if (expected5 == result5) {
        std::cout << "magnitude function working\n";
    }
    else {
        std::cout << "magnitude product function FAILED!\n";
        failure = 1;
    }

    expected = test * (1/test.mag());
    result = test.unit();
    if (expected == result) {
        std::cout << "unit vector function working\n";
    }
    else {
        std::cout << "unit vector function FAILED!\n";
        failure = 1;
    }

    expected = vec3(0.0, 0.0, 0.0);
    result = test.cross(test);
    if (expected == result) {
        std::cout << "cross product function working\n";
    }
    else {
        std::cout << "cross product function FAILED!\n";
        failure = 1;
    }

    std::cout << "printing vector by using [] operator: (" << test[0] << ", " << test[1] << ", " << test[2] << ")\n";

    test+= test;
    expected = vec3(5.0, 7.0, 9.0);
    if (expected == test) {
        std::cout << "self-assign add function working\n";
    }
    else {
        std::cout << "self-assign add function FAILED!\n";
        failure = 1;
    }
    
    test*= 4.5;
    expected = vec3(22.5, 31.5, 40.5);
    if (expected == test) {
        std::cout << "self-assign scalar mult function working\n";
    }
    else {
        std::cout << "self-assign scalar mult function FAILED!\n";
        failure = 1;
    }

    test-= test;
    expected = vec3(0, 0, 0);
    if (expected == test) {
        std::cout << "self-assign subtract function working\n";
    }
    else {
        std::cout << "self-assign subtract function FAILED!\n";
        failure = 1;
    }

    return failure;
}


int ivec3_tester() {
    std::cout << "***** TESTING IVEC3 FUNCTIONALITY *****\n";    
    int failure = 0;

    ivec3 test = ivec3(2, 3, 4);

    ivec3 expected = ivec3(4, 6, 8);
    ivec3 result = test + test;

    int expected5 = static_cast<int>(std::round(std::sqrt(29)));
    int result5 = test.mag();
    if (expected5 == result5) {
        std::cout << "magnitude function working\n";
    }
    else {
        std::cout << "magnitude product function FAILED!\n";
        failure = 1;
    }

    expected = ivec3(static_cast<int>(std::round(2.0f / test.mag())), static_cast<int>(std::round(3.0f / test.mag())), static_cast<int>(std::round(4.0f / test.mag())));
    result = test.unit();
    if (expected == result) {
        std::cout << "unit vector function working\n";
    } 
    else {
        std::cout << "unit vector function FAILED!\n";
        std::cout << result.x << ' ' << result.y << ' ' << result.z << '\n';
        std::cout << expected.x << ' ' << expected.y << ' ' << expected.z << '\n';
        std::cout << 3 / test.mag() << '\n';
        failure = 1;
    }

    return failure;
}


int matrix_tester() {
    std::cout << "***** TESTING MATRIX FUNCTIONALITY *****\n";    
    int failure = 0;

    float testBuilder[MATRIX_MAX][MATRIX_MAX] = {{1.5, 2.5, 3.5}, {2.5, 3.5, 4.5}, {3.5, 4.5, 5.5}};
    Matrix test = Matrix(testBuilder);
    Matrix copy{test};

    if (test != copy) {
        std::cout << "copy constructor FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "copy constructor working\n";
    }

    Matrix equalsCopy = test;

    if (test != equalsCopy) {
        std::cout << "operator= FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "operator= working\n";
    }
    
    Matrix testProd = test * test;
    float resultBuilder[MATRIX_MAX][MATRIX_MAX] = {{20.75, 28.25, 35.75}, {28.25, 38.75, 49.25}, {35.75, 49.25, 62.75}};
    Matrix result = Matrix(resultBuilder);
    if (result != testProd) {
        std::cout << "matrix multiplication function FAILED!\n";
        failure = 1;
    }
    else {
        std::cout << "matrix multiplication function working\n";
    }

    float testBuilder9[MATRIX_MAX][MATRIX_MAX] = {{1.5, 2.5, 3.5}, {4.5, 5.5, 6.5}, {7.5, 8.5, 9.5}};
    float testBuilderT[MATRIX_MAX][MATRIX_MAX] = {{1.5, 4.5, 7.5}, {2.5, 5.5, 8.5}, {3.5, 6.5, 9.5}};
    Matrix test9 = Matrix(testBuilder9);
    Matrix transpose = Matrix(testBuilderT);
    if (test9.transpose() == transpose) {
        std::cout << "transpose function working\n";
    }
    else {
        std::cout << "transpose function FAILED!\n";
        failure = 1;
    }

    return failure;
}