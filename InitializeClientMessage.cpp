#include "InitializeClientMessage.hpp"

InitializeClientMessage::InitializeClientMessage(std::vector<ElementParameters> els) : SocketMessage<InitializeClientMessage>(MessageType::INITIALIZE_CLIENT), elements(els) {}

std::string InitializeClientMessage::serialize() {
    return "";
}

json InitializeClientMessage::toJsonImpl() {
    json j;
    return j;
}