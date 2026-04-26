#ifndef __INITIALIZE_CLIENT_MESSAGE_HPP__
#define __INITIALIZE_CLIENT_MESSAGE_HPP__

#include "SocketMessage.hpp"
#include "./external/json.hpp"
#include "ElementParameters.hpp"
#include <vector>

class InitializeClientMessage : public SocketMessage<InitializeClientMessage> {
    public:
        InitializeClientMessage(std::vector<ElementParameters> els);
        json toJsonImpl();
    private:
        std::vector<ElementParameters> elements;
};

#endif