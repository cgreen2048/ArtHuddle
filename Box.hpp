#ifndef __BOX_HPP__
#define __BOX_HPP__

#include "GuiElement.hpp"

class Box : public GuiElement {
	public:
		enum class TagType { Vec, IVec };
	private:
		ivec2 min;
		ivec2 max;
		ivec3 color;
		TagType minType = TagType::Vec;
		TagType maxType = TagType::Vec;
		TagType colorType = TagType::Vec;

	public:
		Box();
		Box(ivec2, ivec2, ivec3);
		Box(const Box&);
		Box& operator=(const Box&);
		bool operator==(Box);
		bool operator!=(Box);
		~Box();
		void draw();
		void setMin(const ivec2& v, TagType t);
		void setMax(const ivec2& v, TagType t);
		void setColor(const ivec3& v, TagType t);
		void writeXml(std::ostream& out) const;
		
};

#endif