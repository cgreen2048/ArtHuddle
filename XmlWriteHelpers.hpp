#ifndef __XML_WRITE_HELPERS_HPP__
#define __XML_WRITE_HELPERS_HPP__
#include <ostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "ivec2.hpp"
#include "ivec3.hpp"

inline vec2 toVec2(const ivec2& v) {
    return vec2(static_cast<float>(v.x), static_cast<float>(v.y));
}

inline vec3 toVec3(const ivec3& v) {
    return vec3(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
}

inline void writeVec2(std::ostream& out, const vec2& v) {
    out << "    <vec2>\n";
    out << "        <x>" << v.x << "</x>\n";
    out << "        <y>" << v.y << "</y>\n";
    out << "    </vec2>\n";
}

inline void writeIVec2(std::ostream& out, const ivec2& v) {
    out << "    <ivec2>\n";
    out << "        <x>" << v.x << "</x>\n";
    out << "        <y>" << v.y << "</y>\n";
    out << "    </ivec2>\n";
}

inline void writeVec3(std::ostream& out, const vec3& v) {
    out << "    <vec3>\n";
    out << "        <x>" << v.x << "</x>\n";
    out << "        <y>" << v.y << "</y>\n";
    out << "        <z>" << v.z << "</z>\n";
    out << "    </vec3>\n";
}

inline void writeIVec3(std::ostream& out, const ivec3& v) {
    out << "    <ivec3>\n";
    out << "        <x>" << v.x << "</x>\n";
    out << "        <y>" << v.y << "</y>\n";
    out << "        <z>" << v.z << "</z>\n";
    out << "    </ivec3>\n";
}

#endif