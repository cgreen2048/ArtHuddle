#include "ArtHuddle/network/RelayServer.hpp"
#include "ArtHuddle/utility/ThreadPool.hpp"
#include "ArtHuddle/network/InitializeClientMessage.hpp"

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

RelayServer::RelayServer(Layout* layout)
    : running(false), listener(INVALID_SOCKET), messageHandler(MessageHandler(layout)) {}

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

    ThreadPool pool;

    while (this->running) {
        SocketType client = accept(listener, nullptr, nullptr);

        if (client == INVALID_SOCKET) {
            if(!running) {
                std::cout << "Server stopped accepting clients\n";
                break;
            }
            std::cout << "Accept failed\n";
            break;
            #ifdef _WIN32
                    WSACleanup();
            #endif
            return;
        }

        std::cout << "Client connected!\n";

        {
            std::lock_guard<std::mutex> lock(this->clientsMutex);
            this->clients.push_back(client);
        }

        pool.enqueue([this, client]() {
            this->handleClient(client);
        });
    }

    #ifdef _WIN32
        WSACleanup();
    #endif

    running = false;
}

void RelayServer::stop() {
    std::cout << "[Server] Stopping...\n";
    running = false;

    for (SocketType client : clients) {
        shutdown(client, SHUT_RDWR);
        close(client);
    }

    clients.clear();

    if (listener != INVALID_SOCKET) {
        shutdown(listener, SHUT_RDWR);
        CLOSE_SOCKET(listener);
        listener = INVALID_SOCKET;
    }
}

void RelayServer::removeClient(SocketType client) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    clients.erase(
        std::remove(clients.begin(), clients.end(), client),
        clients.end()
    );
}

void RelayServer::handleClient(SocketType client) {
    char buffer[BUFFER_SIZE + 1];
    std::string pending;

    std::vector<ElementParameters> elements = this->messageHandler.getCanvasLayout()->getChildElementParameters();
    InitializeClientMessage init(elements);
    this->sendToClient(init.getSerializedMessage(), client);

    while (this->running) {
        int bytes = recv(client, buffer, BUFFER_SIZE, 0);

        if (bytes <= 0) {
            std::cout << "Client disconnected.\n";
            break;
        }

        pending.append(buffer, bytes);

        size_t newlinePos;
        while ((newlinePos = pending.find('\n')) != std::string::npos) {
            std::string message = pending.substr(0, newlinePos);
            pending.erase(0, newlinePos + 1);

            if (!message.empty()) {
                this->messageHandler.push(message);
                broadcast(message + "\n", client);
            }
        }
    }

    // Cleanup
    this->removeClient(client);
    CLOSE_SOCKET(client);
}

void RelayServer::sendToClient(const std::string& message, SocketType client) {
    ssize_t sent = send(client, message.c_str(), message.size(), 0);
    
    if (sent < 0) {
        std::cerr << "Failed to send message\n";
    }
}

void RelayServer::broadcast(const std::string& message, SocketType clientSender) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (SocketType client : this->clients) {
        if (client == clientSender) {
            continue;
        }
        ssize_t sent = send(client, message.c_str(), message.size(), 0);
    
        if (sent < 0) {
            std::cerr << "Failed to send message\n";
        }
    }
}

void RelayServer::processMessages() {
    this->messageHandler.processMessages();
}