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
		Point(ivec2 coords, ivec3 color);
		Point(const Point& cp);
		Point& operator=(const Point& cp);
		bool operator==(Point rhs);
		bool operator!=(Point rhs);
		~Point();
		void draw(Screen *screen);
		void setCoords(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		void writeXml(std::ostream& out, int depth) const;
};

#endif