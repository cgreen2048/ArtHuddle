#ifndef __UPDATE_ELEMENT_MESSAGE_HPP__
#define __UPDATE_ELEMENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "ElementParameters.hpp"
#include "JsonDefinition.hpp"

class UpdateElementMessage : public SocketMessage<UpdateElementMessage> {
    public:
        UpdateElementMessage(ElementParameters ep);
        json toJsonImpl();
    private:
        ElementParameters ep;
};

#endif