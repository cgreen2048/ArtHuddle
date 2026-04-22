#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "GuiElement.hpp"

#define POINT_PADDING 10

class Point : public GuiElement {
	private:
		ivec2 coords;
		ivec3 color;
		TagType coordsType = TagType::Vec;
		TagType colorType = TagType::Vec;
	
	public:
		Point();
		Point(ivec2 coords, ivec3 color);
		Point(ElementParameters ep);
		Point(const Point& cp);
		Point& operator=(const Point& cp);
		bool operator==(Point rhs);
		bool operator!=(Point rhs);
		~Point();
		void draw(Screen *screen);
		GuiElement* clone() const;
		void setCoords(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		ivec2 getCoords();
		void writeXml(std::ostream& out, int depth) const;
		bool isInside(ivec2 coordinates);
		bool validateAndNormalize(ElementParameters& ep);
		ElementParameters getParameters();
		guiElement getType();
};

#endif