#ifndef __GUI_ELEMENT_HPP__
#define __GUI_ELEMENT_HPP__

#include <iostream>

enum class guiElement {POINT, LINE, BOX};




class GuiElement
{
	public:
		GuiElement() 
		{
			std::cout << "GuiElement constructor\n";
		}
		virtual ~GuiElement()
		{
			std::cout << "GuiElement destroyed\n";
		}
		virtual void draw()
		{
			std::cout << "Draw\n";
		}
};

class Point: public GuiElement
{
	public:
		Point()
		{
			std::cout << "Point created\n";
		}
		~Point()
		{
			std::cout << "Point destroyed\n";
		}
		void draw()
		{
			std::cout << "point!\n";
		}
};

class Line: public GuiElement
{
	public:
		Line()
		{
			std::cout << "Line constructor\n";
		}
		~Line()
		{
			std::cout << "Line destroyed\n";
		}
		void draw()
		{
			std::cout << "line!\n";
		}
};

class Box: public GuiElement
{
	public:
		Box()
		{
			std::cout << "Box constructor\n";
		}
		~Box()
		{
			std::cout << "Box destroyed\n";
		}
		void draw()
		{
			std::cout << "box!\n";
		}
};


#endif
