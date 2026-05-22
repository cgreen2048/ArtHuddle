#include "ArtHuddle/network/DrawElementMessage.hpp"
#include "ArtHuddle/core/jsonHelpers.hpp"

DrawElementMessage::DrawElementMessage(ElementParameters ep) : SocketMessage<DrawElementMessage>(MessageType::DRAW_ELEMENT), ep(ep) {}

json DrawElementMessage::toJsonImpl() {
    return elementParametersToJson(ep);
}