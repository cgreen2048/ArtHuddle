#ifndef __XML_WRITE_HELPERS_HPP__
#define __XML_WRITE_HELPERS_HPP__
#include <ostream>
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"


inline vec2 toVec2(const ivec2& v) {
    return vec2(static_cast<float>(v.x), static_cast<float>(v.y));
}

inline vec3 toVec3(const ivec3& v) {
    return vec3(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
}

inline void writeVec2(std::ostream& out, const vec2& v, const std::string pad) {
    out << pad << "    <vec2>\n";
    out << pad << "        <x>" << v.x << "</x>\n";
    out << pad << "        <y>" << v.y << "</y>\n";
    out << pad << "    </vec2>\n";
}

inline void writeIVec2(std::ostream& out, const ivec2& v, const std::string pad) {
    out << pad << "    <ivec2>\n";
    out << pad << "        <x>" << v.x << "</x>\n";
    out << pad << "        <y>" << v.y << "</y>\n";
    out << pad << "    </ivec2>\n";
}

inline void writeVec3(std::ostream& out, const vec3& v, const std::string pad) {
    out << pad << "    <vec3>\n";
    out << pad << "        <x>" << v.x << "</x>\n";
    out << pad << "        <y>" << v.y << "</y>\n";
    out << pad << "        <z>" << v.z << "</z>\n";
    out << pad << "    </vec3>\n";
}

inline void writeIVec3(std::ostream& out, const ivec3& v, const std::string pad ) {
    out << pad << "    <ivec3>\n";
    out << pad << "        <x>" << v.x << "</x>\n";
    out << pad << "        <y>" << v.y << "</y>\n";
    out << pad << "        <z>" << v.z << "</z>\n";
    out << pad << "    </ivec3>\n";
}

#endif