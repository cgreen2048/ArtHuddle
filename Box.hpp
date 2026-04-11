#ifndef __BOX_HPP__
#define __BOX_HPP__

#include "GuiElement.hpp"

class Box : public GuiElement {
	protected:
		ivec2 min;
		ivec2 max;
		ivec3 color;
		TagType minType = TagType::Vec;
		TagType maxType = TagType::Vec;
		TagType colorType = TagType::Vec;

	public:
		Box();
		Box(ivec2 min, ivec2 max, ivec3 color);
		Box(ElementParameters ep);
		Box(const Box& cp);
		Box& operator=(const Box& rhs);
		bool operator==(Box rhs);
		bool operator!=(Box rhs);
		~Box();
		void draw(Screen *screen);
		void setMin(const ivec2& v, TagType t);
		void setMax(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		ivec2 getMin();
		ivec2 getMax();
		void writeXml(std::ostream& out, int depth) const;
		bool isValid(ElementParameters ep);
		bool inBounds(const ivec2& point) const;
		bool isInside(ivec2 coordinates);
};

#endif