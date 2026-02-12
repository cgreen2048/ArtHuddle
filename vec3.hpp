#ifndef __VEC_THREE_HPP__
#define __VEC_THREE_HPP__

#include <cmath>
#include <iostream>
#include <string>

// Header file for Tvec3

template <typename T>
class Tvec3 {
    private:
        T components[3];
    public:
        T& x, &y, &z;

        Tvec3() : components{0, 0, 0}, x(components[0]), y(components[1]), z(components[2]) {
        
        }

        Tvec3(const Tvec3& cp) : Tvec3() { 
            x = cp.x;
            y = cp.y;
            z = cp.z;
        }

        Tvec3(T _x, T _y, T _z) : Tvec3() { 
            x = _x;
            y = _y;
            z = _z;
        }

        Tvec3& operator=(const Tvec3& cp) { 
            if (this == &cp) {
                return *this;
            }
            x = cp.x;
            y = cp.y;
            z = cp.z;
            
            return *this;
        }

        T dot(Tvec3 rhs) {  
            return x * rhs.x + y * rhs.y + z * rhs.z;
        }

        T mag() {   
            return static_cast<T>(std::sqrt(x * x + y * y + z * z));
        }

        Tvec3 unit() { 
            T magnitude = mag();
            if (magnitude == 0) {
              return Tvec3{0,0,0};
            }
            T magnitudeReciprocal = 1 / magnitude;
            return Tvec3{x * magnitudeReciprocal, y * magnitudeReciprocal, z * magnitudeReciprocal};
        }

        Tvec3 cross(Tvec3 rhs) {    
            T xComp = y * rhs.z - z * rhs.y;
            T yComp = z * rhs.x - x * rhs.z;
            T zComp = x * rhs.y - y * rhs.x;

            return Tvec3{xComp, yComp, zComp};
        }

        bool operator==(Tvec3 rhs) {   
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        bool operator!=(Tvec3 rhs) {   
            return x != rhs.x || y != rhs.y || z != rhs.z;
        }

        T& operator[](int index) {   
            if ((index < 0) || (index > sizeof(components)/sizeof(components[0]))) {
                std::cerr << "ERROR: ACCESSING MEMORY OUTSIDE OF SCOPE\n";
                exit(1);
            }
            return components[index];
        }

        Tvec3& operator+=(Tvec3 rhs) { 
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        Tvec3 operator+(Tvec3 rhs) {  
            return Tvec3(*this) += rhs;
        }

        Tvec3& operator*=(T scalar) {   
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Tvec3 operator*(T scalar) {    
            return Tvec3(*this) *= scalar;
        }

        Tvec3& operator-=(Tvec3 rhs) { 
            *this += (rhs * -1);
            return *this;
        }

        Tvec3 operator-(Tvec3 rhs) {  
            return Tvec3(*this) -= rhs;
        }
};

typedef Tvec3<float> vec3;
typedef Tvec3<int> ivec3;

// Specialization for ivec3 magnitude: rounds to nearest integer then casts
template<>
inline int Tvec3<int>::mag() {
  return static_cast<int>(std::round(std::sqrt(x * x + y * y + z * z)));
}

// Specialization for ivec3 unit: rounds to nearest integer and casts for each component
template<>
inline ivec3 Tvec3<int>::unit() {
  float magnitude = mag();
  if (magnitude == 0) {
    return ivec3{0,0,0};
  }
  float magnitudeReciprocal = 1 / magnitude;
  return ivec3{
    static_cast<int>(std::round(x * magnitudeReciprocal)), 
    static_cast<int>(std::round(y * magnitudeReciprocal)),
    static_cast<int>(std::round(z * magnitudeReciprocal))
  };
}
#endif