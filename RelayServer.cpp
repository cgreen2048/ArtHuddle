#include "RelayServer.hpp"

#include <iostream>
#include <cstring>

#ifdef _WIN32
    #define CLOSE_SOCKET closesocket
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define CLOSE_SOCKET close
#endif

#define PORT 40666
#define BUFFER_SIZE 512

RelayServer::RelayServer()
    : running(false), listener(INVALID_SOCKET) {}

void RelayServer::start() {
    running = true;

#ifdef _WIN32
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed\n";
        return;
    }
#endif

    listener = socket(AF_INET, SOCK_STREAM, 0);

    if (listener == INVALID_SOCKET) {
        std::cout << "Socket creation failed\n";
        return;
    }

    int opt = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listener, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << "Bind failed\n";
        CLOSE_SOCKET(listener);
        return;
    }

    if (listen(listener, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Listen failed\n";
        CLOSE_SOCKET(listener);
        return;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    SocketType client = accept(listener, nullptr, nullptr);

    if (client == INVALID_SOCKET) {
        std::cout << "Accept failed\n";
        CLOSE_SOCKET(listener);
        return;
    }

    std::cout << "Client connected!\n";

    char buffer[BUFFER_SIZE + 1];

    while (running) {
        int bytes = recv(client, buffer, BUFFER_SIZE, 0);

        if (bytes <= 0) {
            std::cout << "Client disconnected\n";
            break;
        }

        buffer[bytes] = '\0';
        std::cout << "Received: " << buffer << "\n";
    }

    CLOSE_SOCKET(client);
    CLOSE_SOCKET(listener);

#ifdef _WIN32
    WSACleanup();
#endif

    running = false;
}

void RelayServer::stop() {
    std::cout << "[Server] Stopping...\n";
    running = false;

    if (listener != INVALID_SOCKET) {
        CLOSE_SOCKET(listener);
        listener = INVALID_SOCKET;
    }
}