#ifndef __SOCKET_MESSAGE_HPP__
#define __SOCKET_MESSAGE_HPP__

#include "JsonDefinition.hpp"
#include "MessageTypes.hpp"
#include <string>


template <typename Message>
class SocketMessage {
    public: 
        SocketMessage(MessageType type) {
            this->messageType = type;
        };
        void serialize() {
            json jsonData = this->toJson();
            serializedMessage = jsonData.dump() + "\n";
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
        std::string serializedMessage = "";
};

#endif