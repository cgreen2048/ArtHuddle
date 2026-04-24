#ifndef __LAYOUT_HPP__
#define __LAYOUT_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "Screen.hpp"
#include "GuiElement.hpp"
#include "vec2.hpp"
#include "Event.hpp"

class Layout : public GuiElement {
    private:
        vec2 start;
        vec2 end;
        bool hasParentStart = false;
        bool hasParentEnd = false;
        std::vector<GuiElement*> elements;
        bool active;
    public:
        Layout();
        Layout(ElementParameters ep);
        ~Layout();
        vec2 getStart() const;
        vec2 getEnd() const;
        void setStart(const vec2& start);
        void setEnd(const vec2& end);
        void setParentStart(const ivec2& start);
        void setParentEnd(const ivec2& end);
        void setActive(bool value);
        bool isActive();
        void addElement(GuiElement *element);
        void draw(Screen *screen);
        GuiElement* clone() const;
        void drawOverlay(Screen *screen);
        void writeXml(std::ostream& out, int depth = 0) const;
        bool resolveEvent(Event* e);
        GuiElement* getElementAt(const ivec2& point);
        const std::vector<GuiElement*>& getElements() const;
        int getAbsoluteStartX();
        int getAbsoluteStartY();
        int getAbsoluteEndX();
        int getAbsoluteEndY();
        bool isInside(ivec2 coordinates);
        void clearElements();
        void deleteElement(const std::string& elementName);
        bool validateAndNormalize(ElementParameters& ep);
        ElementParameters getParameters();
        guiElement getType();
        void setBounds();
		std::vector<ivec2> getBounds();
};

#endif