#ifndef __INTERACTION_STATE_HPP__
#define __INTERACTION_STATE_HPP__

enum class InteractionState { 
    IDLE, 
    FREEHAND_DRAWING, 
    SHAPE_DRAWING, 
    DRAGGING,
    TOOLBAR_CLICK 
};

#endif