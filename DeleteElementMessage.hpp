#ifndef __DELETE_ELEMENT_MESSAGE_HPP__
#define __DELETE_ELEMENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "./external/JsonDefinition.hpp"
#include <string>

class DeleteElementMessage : public SocketMessage<DeleteElementMessage> {
    public:
        DeleteElementMessage(std::string elementName);
        json toJsonImpl();
    private:
        std::string elementName;
};

#endif