#ifndef __TEXT_MESSAGE_HPP__
#define __TEXT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "JsonDefinition.hpp"
#include <string>

class UpdateTextMessage : public SocketMessage<UpdateTextMessage> {
    public:
        UpdateTextMessage(std::string elementName, std::string text);
        json toJsonImpl();
    private:
        std::string elementName;
        std::string text;
};

#endif