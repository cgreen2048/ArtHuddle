#include "UpdateElementMessage.hpp"
#include "jsonHelpers.hpp"

UpdateElementMessage::UpdateElementMessage(ElementParameters ep) : SocketMessage<UpdateElementMessage>(MessageType::UPDATE_ELEMENT), ep(ep) {}

json UpdateElementMessage::toJsonImpl() {
    return elementParametersToJson(ep);
}
