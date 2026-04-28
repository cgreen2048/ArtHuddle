// ElementTypes.hpp
#ifndef __ELEMENT_TYPES_HPP__
#define __ELEMENT_TYPES_HPP__

enum class MessageType {
    DRAW_ELEMENT,
    DELETE_ELEMENT,
    UPDATE_ELEMENT,
    INITIALIZE_CLIENT
};

enum class guiElement {
    POINT, LINE, BOX, TRIANGLE, ELLIPSE, ARROW,
    TEXTBOX, FREEHAND, BUTTON, LAYOUT, INPUTTEXTBOX, UNKNOWN
};

enum class TagType {
    Vec,
    IVec
};

#endif