#ifndef __UPDATE_ELEMENT_MESSAGE_HPP__
#define __UPDATE_ELEMENT_MESSAGE_HPP__

#include "ArtHuddle/core/SocketMessage.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include "../external/JsonDefinition.hpp"

class UpdateElementMessage : public SocketMessage<UpdateElementMessage> {
    public:
        UpdateElementMessage(ElementParameters ep);
        json toJsonImpl();
    private:
        ElementParameters ep;
};

#endif