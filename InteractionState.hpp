#ifndef __INTERACTION_STATE_HPP__
#define __INTERACTION_STATE_HPP__

enum class InteractionState { 
    IDLE, 
    FREEHAND_DRAWING, 
    SHAPE_DRAWING, 
    SHAPE_COMPLETED,
    DRAGGING,
    TOOLBAR_CLICK,
    ELEMENT_PRESSED
};

#endif