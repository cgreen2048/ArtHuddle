#ifndef __UPDATE_ELEMENT_MESSAGE_HPP__
#define __UPDATE_ELEMENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "ElementParameters.hpp"
#include "./external/json.hpp"
#include <string>

class UpdateElementMessage : public SocketMessage<UpdateElementMessage> {
    public:
        UpdateElementMessage(ElementParameters ep);
        std::string serializeImpl();
        json toJsonImpl();
    private:
        ElementParameters elementParameters;
};

#endif