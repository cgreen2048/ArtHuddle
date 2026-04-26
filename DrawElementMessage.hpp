#ifndef __DRAW_ELEMENT_MESSAGE_HPP__
#define __DRAW_ELEMENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "ElementParameters.hpp"
#include "JsonDefinition.hpp"

class DrawElementMessage : public SocketMessage<DrawElementMessage> {
    public:
        DrawElementMessage(ElementParameters ep);
        json toJsonImpl();
    private:
        ElementParameters ep;
};

#endif