#include "UpdateTextMessage.hpp"

UpdateTextMessage::UpdateTextMessage(std::string elementName, std::string text) : SocketMessage<UpdateTextMessage>(MessageType::UPDATE_TEXT), elementName(elementName), text(text) {}

json UpdateTextMessage::toJsonImpl() {
    json j;
    j["name"] = elementName;
    j["text"] = this->text;
    return j;
}

