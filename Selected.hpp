#ifndef __SELECTED_HPP__
#define __SELECTED_HPP__

#include "GuiElement.hpp"

class Selected {
    private:
        Selected();
        ~Selected();
        GuiElement* selectedElement;
        ivec2 minBound;
        ivec2 maxBound;
    
    public:
        static Selected& getInstance();
        Selected(const Selected&) = delete;
        Selected& operator=(const Selected&) = delete;
        void setSelectedElement(GuiElement* updatedElement);
        GuiElement* getSelectedElement();
};

#endif