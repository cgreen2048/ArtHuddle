#ifndef __VEC2_HPP__
#define __VEC2_HPP__

#include <cmath>
#include <iostream>
#include <string>

// Header file for vec2, ivec2

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
        T& operator[](int index) {   // access via array notation
                                    // Can do a mutable operation like v[0] = 5
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


#endif
