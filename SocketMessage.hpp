#ifndef __SOCKET_MESSAGE_HPP__
#define __SOCKET_MESSAGE_HPP__

#include "./external/json.hpp"
#include <string>

enum class MessageType {
    DRAW_ELEMENT,
    DELETE_ELEMENT,
    UPDATE_ELEMENT,
    INITIALIZE_CLIENT
};

template <typename Message>
class SocketMessage {
    public: 
        SocketMessage(MessageType type) {
            this->messageType = type;
        };
        void serialize() {
            this->serializedMessage = static_cast<Message*>(this)->serializeImpl();
        }
        json toJson() {
            json j = static_cast<Message*>(this)->toJsonImpl();
            j["messageType"] = static_cast<int>(this->messageType);
            return j;
        }
        std::string getSerializedMessage() {
            if (this->serializedMessage.empty()) {
                this->serialize();
            }
            return this->serializedMessage;
        }

    protected: 
        MessageType messageType;
        std::string serializedMessage = ""
};

#endif

// need a way to send messages from Client to Server and Server to Client where we pass in
// one ElementParameters struct that contains all necessary info to create an element on the client side
// or a list of ElementParameters on connection to send all existing elements to the client