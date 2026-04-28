#include "DeleteElementMessage.hpp"

DeleteElementMessage::DeleteElementMessage(std::string elementName) : SocketMessage<DeleteElementMessage>(MessageType::DELETE_ELEMENT), elementName(elementName) {}

json DeleteElementMessage::toJsonImpl() {
    json j;
    j["name"] = elementName;
    return j;
}

