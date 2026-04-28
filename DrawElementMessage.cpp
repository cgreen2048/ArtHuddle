#include "DrawElementMessage.hpp"
#include "jsonHelpers.hpp"

DrawElementMessage::DrawElementMessage(ElementParameters ep) : SocketMessage<DrawElementMessage>(MessageType::DRAW_ELEMENT), ep(ep) {}

json DrawElementMessage::toJsonImpl() {
    return elementParametersToJson(ep);
}