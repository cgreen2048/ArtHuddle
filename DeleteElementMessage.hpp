#ifndef __DELETE_ELEMENT_MESSAGE_HPP__
#define __DELETE_ELEMENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "./external/json.hpp"
#include <string>

class DeleteElementMessage : public SocketMessage<DeleteElementMessage> {
    public:
        DeleteElementMessage(std::string elementName);
        std::string serializeImpl();
        json toJsonImpl();
    private:
        std::string elementName;
};

#endif