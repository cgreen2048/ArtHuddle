#ifndef __VEC_HPP__
#define __VEC_HPP__

#include <cmath>
#include <iostream>
#include <string>
#define MATRIX_MAX 3

// Header file for vec2, ivec2, vec3, ivec3, Matrix classes
// Hunter Flick

template <typename T>
class Tvec2 {
    private:
        T components[2];
    
    public:
        Tvec2() : components{0, 0}, x(components[0]), y(components[1]) {
            // placeholder
        }
        Tvec2(const Tvec2& cp) : Tvec2() { // Constructor delegation
            x = cp.x;
            y = cp.y;
        }
        Tvec2(T _x, T _y) : Tvec2() { // Constructor delegation
            x = _x;
            y = _y;
        }
        Tvec2& operator=(const Tvec2& cp) { // This is not a constructor, if this function is invoked then the object already exists
            if (this == &cp) {
                return *this;
            }
            this->x = cp.x;
            this->y = cp.y;
            
            return *this;
        }
        T dot(Tvec2 rhs) {  // dot product
            return this->x * rhs.x + this->y * rhs.y;
        }
        T mag() {   // magnitude
            return std::sqrt(this->x * this->x + this->y * this->y);
        }
        Tvec2 unit() {  // unit vector
            T magnitude = this->mag();
            return Tvec2{this->x / magnitude, this->y / magnitude};
        }
        bool operator==(Tvec2 rhs) {    // equality
            if ((this->x == rhs.x) && (this->y == rhs.y)) return true;
            return false;
        }
        bool operator!=(Tvec2 rhs) {    // non-equality
            if ((this->x == rhs.x) && (this->y == rhs.y)) return false;
            return true;
        }
        T operator[](int index) {   // access via array notation
            if ((index < 0) || (index > sizeof(components)/sizeof(components[0]))) {
                std::cerr << "ERROR: ACCESSING MEMORY OUTSIDE OF SCOPE\n";
                exit(1);
            }
            return components[index];
        }
        Tvec2& operator+=(Tvec2 rhs) {  // addition self-assign
            this->x += rhs.x;
            this->y += rhs.y;
            return *this;
        }
        Tvec2 operator+(Tvec2 rhs) {    // addition
            return Tvec2(*this) += rhs;
        }
        Tvec2& operator*=(T scalar) {   // scalar mult self-assign
            this->x *= scalar;
            this->y *= scalar;
            return *this;
        }
        Tvec2 operator*(T scalar) {    // scalar mult
            return Tvec2(*this) *= scalar;
        }
        Tvec2& operator-=(Tvec2 rhs) {  // subtraction self-assign
            *this += (rhs * -1);
            return *this;
        }
        Tvec2 operator-(Tvec2 rhs) {    // subtraction
            return Tvec2(*this) -= rhs;
        }

        T& x, &y;
};

typedef Tvec2<float> vec2;  // alias for class

typedef Tvec2<int> ivec2;
template <>
inline int Tvec2<int>::mag() {  // specialization for magnitude of ivec2, rounds to nearest integer and then casts, use inline to get around mult def error
    return static_cast<int>(std::round(std::sqrt(this->x * this->x + this->y * this->y)));
}
template<>
inline ivec2 Tvec2<int>::unit() {  // specialization for unit vector of ivec2, rounds to nearest integer and then casts for each component
    int magnitude = this->mag();
    return ivec2{static_cast<int>(std::round(this->x / magnitude)), static_cast<int>(std::round(this->y / magnitude))};
}


template <typename T>
class Tvec3 {
    private:
        T components[3];
    
    public:
        Tvec3() : components{0, 0, 0}, x(components[0]), y(components[1]), z(components[2]) {
            // placeholder
        }
        Tvec3(const Tvec3& cp) : Tvec3() { // Constructor delegation
            x = cp.x;
            y = cp.y;
            z = cp.z;
        }
        Tvec3(T _x, T _y, T _z) : Tvec3() { // Constructor delegation
            x = _x;
            y = _y;
            z = _z;
        }
        Tvec3& operator=(const Tvec3& cp) { // This is not a constructor, if this function is invoked then the object already exists
            if (this == &cp) {
                return *this;
            }
            this->x = cp.x;
            this->y = cp.y;
            this->z = cp.z;
            
            return *this;
        }
        T dot(Tvec3 rhs) {  // dot product
            return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
        }
        T mag() {   // magnitude
            return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
        }
        Tvec3 unit() {  // unit vector
            T magnitude = this->mag();
            return Tvec3{this->x / magnitude, this->y / magnitude, this->z / magnitude};
        }
        Tvec3 cross(Tvec3 rhs) {    // cross product
            T xComp = this->y * rhs.z - this->z * rhs.y;
            T yComp = this->z * rhs.x - this->x * rhs.z;
            T zComp = this->x * rhs.y - this->y * rhs.x;

            return Tvec3{xComp, yComp, zComp};
        }
        bool operator==(Tvec3 rhs) {    // equality
            if ((this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z)) return true;
            return false;
        }
        bool operator!=(Tvec3 rhs) {    // non-equality
            if ((this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z)) return false;
            return true;
        }
        T operator[](int index) {   // accessing elements array style
            if ((index < 0) || (index > sizeof(components)/sizeof(components[0]))) {
                std::cerr << "ERROR: ACCESSING MEMORY OUTSIDE OF SCOPE\n";
                exit(1);
            }
            return components[index];
        }
        Tvec3& operator+=(Tvec3 rhs) {  // addition self-assign
            this->x += rhs.x;
            this->y += rhs.y;
            this->z += rhs.z;
            return *this;
        }
        Tvec3 operator+(Tvec3 rhs) {    // addition
            return Tvec3(*this) += rhs;
        }
        Tvec3& operator*=(T scalar) {   // scalar mult self-assign
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }
        Tvec3 operator*(T scalar) {    // scalar mult
            return Tvec3(*this) *= scalar;
        }
        Tvec3& operator-=(Tvec3 rhs) {  // subtraction self-assign
            *this += (rhs * -1);
            return *this;
        }
        Tvec3 operator-(Tvec3 rhs) {    // subtraction
            return Tvec3(*this) -= rhs;
        }

        T& x, &y, &z;
};

typedef Tvec3<float> vec3;

typedef Tvec3<int> ivec3;
template <>
inline int Tvec3<int>::mag() {  // specialization for magnitude of ivec3, rounds to nearest integer and then casts
    return static_cast<int>(std::round(std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z)));
}
template<>
inline ivec3 Tvec3<int>::unit() {  // specialization for unit vector of ivec3, rounds to nearest integer and then casts for each component
    int magnitude = this->mag();
    return ivec3{static_cast<int>(std::round(this->x / magnitude)), static_cast<int>(std::round(this->y / magnitude)), static_cast<int>(std::round(this->z / magnitude))};
}



class Matrix {  // not templated, implementation moved to source file
    private:
        float components[MATRIX_MAX][MATRIX_MAX];
    
    public:
        Matrix();    
        Matrix(float[MATRIX_MAX][MATRIX_MAX]);
        Matrix(const Matrix&);
        Matrix& operator=(const Matrix&);
        vec3 operator[](int);
        bool operator==(Matrix);
        bool operator!=(Matrix);
        Matrix operator*(Matrix);
        Matrix transpose();
};

#endif
