#include "DeleteElementMessage.hpp"

DeleteElementMessage::DeleteElementMessage(std::string elementName) : SocketMessage<DeleteElementMessage>(MessageType::DELETE_ELEMENT), elementName(elementName) {}

std::string DeleteElementMessage::serializeImpl() {
    return "";
}

json DeleteElementMessage::toJsonImpl() {
    json j;
    return j;
}

