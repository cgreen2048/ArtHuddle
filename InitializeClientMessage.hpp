#ifndef __INITIALIZE_CLIENT_MESSAGE_HPP__
#define __INITIALIZE_CLIENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "./external/json.hpp"
#include "ElementParameters.hpp"
#include <vector>
#include <string>

class InitializeClientMessage : public SocketMessage<InitializeClientMessage> {
    public:
        InitializeClientMessage(std::vector<ElementParameters> els);
        std::string serializeImpl();
        json toJsonImpl();
    private:
        std::vector<ElementParameters> elements;
};

#endif