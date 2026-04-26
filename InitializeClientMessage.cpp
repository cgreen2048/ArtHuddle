#include "InitializeClientMessage.hpp"
#include "jsonHelpers.hpp"

InitializeClientMessage::InitializeClientMessage(std::vector<ElementParameters> els) : SocketMessage<InitializeClientMessage>(MessageType::INITIALIZE_CLIENT), elements(els) {}

json InitializeClientMessage::toJsonImpl() {
    json j;
    j["elements"] = json::array()
    for (const auto& ep : elements) {
        j["elements"].push_back(elementParametersToJson(ep));
    }
    return j;
}