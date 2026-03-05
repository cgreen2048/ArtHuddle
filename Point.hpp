#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "GuiElement.hpp"

class Point : public GuiElement {
	public:
		enum class TagType { Vec, IVec };
	private:
		ivec2 coords;
		ivec3 color;
		TagType coordsType = TagType::Vec;
		TagType colorType = TagType::Vec;
	
	public:
		Point();
		Point(ivec2, ivec3);
		Point(const Point&);
		Point& operator=(const Point&);
		bool operator==(Point);
		bool operator!=(Point);
		~Point();
		void draw();
		void setCoords(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		void writeXml(std::ofstream& out) const
};

#endif