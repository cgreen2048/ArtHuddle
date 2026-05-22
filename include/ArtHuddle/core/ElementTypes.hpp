// ElementTypes.hpp
#ifndef __ELEMENT_TYPES_HPP__
#define __ELEMENT_TYPES_HPP__

enum class guiElement {
    POINT, LINE, BOX, TRIANGLE, ELLIPSE, ARROW,
    TEXTBOX, FREEHAND, BUTTON, LAYOUT, INPUTTEXTBOX, UNKNOWN
};

enum class TagType {
    Vec,
    IVec
};

#endif