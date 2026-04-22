#ifndef __GUI_ELEMENT_HPP__
#define __GUI_ELEMENT_HPP__

#include <iostream>
#include "Screen.hpp"
#include "ElementParameters.hpp"
#include "Event.hpp"

enum class guiElement {FREEHAND, LINE, BOX, TRIANGLE, ELLIPSE, ARROW, TEXTBOX, POINT, BUTTON, LAYOUT, UNKNOWN};

class GuiElement {
	protected:
		ivec2 parentStart;
		ivec2 parentEnd;
		std::string name = "";
	public:
		GuiElement();
		
		virtual ~GuiElement();
		
		virtual void draw(Screen*);

		virtual void drawOverlay(Screen*);

		virtual void writeXml(std::ostream& out, int depth) const;

		virtual void setParentStart(const ivec2& start);

        virtual void setParentEnd(const ivec2& end);

		virtual bool resolveEvent(Event* e);

		virtual GuiElement* clone() const = 0;

		void setName(const std::string& n);

		ivec2 getParentStart();

        ivec2 getParentEnd();

		const std::string& getName() const;
		
		virtual bool isInside(ivec2 coordinates) = 0;
		
		virtual bool validateAndNormalize(ElementParameters& ep) = 0;
		
		virtual ElementParameters getParameters() = 0;

		virtual guiElement getType() = 0;
};


#endif
