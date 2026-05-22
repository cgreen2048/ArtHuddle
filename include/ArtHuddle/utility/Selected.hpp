#ifndef __SELECTED_HPP__
#define __SELECTED_HPP__

#include <algorithm>
#include "ArtHuddle/core/vec2.hpp"

class GuiElement;
class Layout;

class Selected {
    private:
        Selected();
        ~Selected();
        GuiElement* selectedElement;
        Layout* selectedLayout;
        ivec2 minBound;
        ivec2 maxBound;
    
    public:
        static Selected& getInstance();
        Selected(const Selected&) = delete;
        Selected& operator=(const Selected&) = delete;
        void setSelectedElement(GuiElement* updatedElement);
        GuiElement* getSelectedElement();
        void setSelectedLayout(Layout* boundingBoxLayout);
        void drawBoundingBox();
        bool isInside(ivec2 coordinates);
};

#endif