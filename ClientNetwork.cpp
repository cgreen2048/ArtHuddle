#include "ClientNetwork.hpp"

int sock = -1;

bool connectToServer(const char* host, int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return false;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &server.sin_addr) <= 0) {
        std::cerr << "Invalid server address\n";
        close(sock);
        sock = -1;
        return false;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&server), sizeof(server)) < 0) {
        std::cerr << "Failed to connect to server: " << host << "\n";
        close(sock);
        sock = -1;
        return false;
    }

    std::cout << "Connected to server: " << host << "\n";
    return true;
}

void sendToServer(const std::string& message) {
    if (sock < 0) {
        std::cerr << "Not connected to server\n";
        return;
    }

    std::string packet = message + "\n";
    ssize_t sent = send(sock, packet.c_str(), packet.size(), 0);

    if (sent < 0) {
        std::cerr << "Failed to send message\n";
    }
}

void receiveMessagesLoop() { // Handles messages relayed from the server. The thread should call this function.
    char buffer[1024];

    while (sock >= 0) {
        std::memset(buffer, 0, sizeof(buffer));

        ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived <= 0) {
            std::cerr << "Disconnected from server\n";
            break;
        }

        std::string message(buffer, bytesReceived);


        std::cout << "Received: " << message << '\n';
    }
}

void closeConnection() {
    if (sock >= 0) {
        close(sock);
        sock = -1;
    }
    std::cout << "Closed client \n";
}