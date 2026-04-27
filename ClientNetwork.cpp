#include "ClientNetwork.hpp"

ClientNetwork::ClientNetwork(Layout* layout) : messageHandler(MessageHandler(layout)) {}

bool ClientNetwork::connectToServer(const char* host, int port) {
    this->socketIdentifier = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketIdentifier < 0) {
        std::cerr << "Failed to create socket\n";
        return false;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &server.sin_addr) <= 0) {
        std::cerr << "Invalid server address\n";
        close(this->socketIdentifier);
        this->socketIdentifier = -1;
        return false;
    }

    if (connect(this->socketIdentifier, reinterpret_cast<sockaddr*>(&server), sizeof(server)) < 0) {
        std::cerr << "Failed to connect to server: " << host << "\n";
        close(this->socketIdentifier);
        this->socketIdentifier = -1;
        return false;
    }

    std::cout << "Connected to server: " << host << "\n";
    this->connected = true;
    return true;
}

void ClientNetwork::sendToServer(const std::string& message) {
    if (!this->connected) {
        std::cerr << "Not connected to server\n";
        return;
    }

    std::string packet = message + "\n";
    ssize_t sent = send(this->socketIdentifier, packet.c_str(), packet.size(), 0);

    if (sent < 0) {
        std::cerr << "Failed to send message\n";
    }
}

void ClientNetwork::receiveMessages() { // Handles messages relayed from the server. The thread should call this function.
    char buffer[1024];

    while (this->socketIdentifier >= 0) {
        std::memset(buffer, 0, sizeof(buffer));

        ssize_t bytesReceived = recv(this->socketIdentifier, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived <= 0) {
            std::cerr << "Disconnected from server\n";
            break;
        }

        std::string message(buffer, bytesReceived);

        this->messageHandler.push(message);
    }
}

void ClientNetwork::processMessages() {
    this->messageHandler.processMessages();
}

void ClientNetwork::closeConnection() {
    if (this->socketIdentifier >= 0) {
        close(this->socketIdentifier);
        this->socketIdentifier = -1;
    }
    this->connected = false;
    std::cout << "Closed client \n";
}