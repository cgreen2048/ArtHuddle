#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "GuiElement.hpp"

class Line : public GuiElement {
	private:
		ivec2 start;
		ivec2 end;
		ivec3 color;
		TagType startType = TagType::Vec;
		TagType endType   = TagType::Vec;
		TagType colorType = TagType::Vec;

	public:
		Line();
		Line(ivec2 start, ivec2 end, ivec3 color);
		Line(ElementParameters ep);
		Line(const Line& cp);
		Line& operator=(const Line& cp);
		bool operator==(Line rhs);
		bool operator!=(Line rhs);
		~Line();
		void draw(Screen *screen);
		GuiElement* clone() const;
		void setStart(const ivec2& v, TagType t);
		void setEnd(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		ivec2 getStart();
		ivec2 getEnd();
		void writeXml(std::ostream& out, int depth) const;
		bool isInside(ivec2 coordinates);
		bool validateAndNormalize(ElementParameters& ep);
		ElementParameters getParameters();
		guiElement getType();
};

#endif