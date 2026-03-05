<<<<<<< HEAD
#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "GuiElement.hpp"

class Line : public GuiElement {
	private:
		vec2 start;
        vec2 end;
		vec3 color;

    public:
		Line();
    
        Line(vec2, vec2, vec3);
		
		~Line();
		
		void draw();
		
};

=======
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
		void writeXml(std::ofstream& out) const;
};

>>>>>>> 5c5799f (Finished XML parser. Refactoring Unit Tests.)
#endif