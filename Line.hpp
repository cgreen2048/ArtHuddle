#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "GuiElement.hpp"

class Line : public GuiElement {
	public:
		enum class TagType { Vec, IVec };
	private:
		ivec2 start;
		ivec2 end;
		ivec3 color;
		TagType startType = TagType::Vec;
		TagType endType   = TagType::Vec;
		TagType colorType = TagType::Vec;

	public:
		Line();
		Line(ivec2, ivec2, ivec3);
		Line(const Line&);
		Line& operator=(const Line&);
		bool operator==(Line);
		bool operator!=(Line);
		~Line();
		void draw();
		void setStart(const ivec2& v, TagType t);
		void setEnd(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		void writeXml(std::ostream& out, int depth) const;
};

#endif