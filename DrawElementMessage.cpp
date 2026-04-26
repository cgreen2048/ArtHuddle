#include "DrawElementMessage.hpp"

DrawElementMessage::DrawElementMessage(ElementParameters ep) : SocketMessage<DrawElementMessage>(MessageType::DRAW_ELEMENT), elementParameters(ep) {}

std::string DrawElementMessage::serializeImpl() {
    return "";
}

json DrawElementMessage::toJsonImpl() {
    json j;
    return j;
}