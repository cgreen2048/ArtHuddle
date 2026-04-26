#include "UpdateElementMessage.hpp"

UpdateElementMessage::UpdateElementMessage(ElementParameters ep) : SocketMessage<UpdateElementMessage>(MessageType::UPDATE_ELEMENT), elementParameters(ep) {}

std::string UpdateElementMessage::serializeImpl() {
    return "";
}

json UpdateElementMessage::toJsonImpl() {
    json j;
    return j;
}
