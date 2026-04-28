#ifndef RELAY_SERVER_HPP
#define RELAY_SERVER_HPP

#include <atomic>
#include <vector>
#include <mutex>
#include <string>
#include <algorithm>
#include "Layout.hpp"
#include "MessageHandler.hpp"

#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    using SocketType = SOCKET;
#else
    using SocketType = int;
#endif

class RelayServer {
public:
    RelayServer(Layout* layout);

    void start();
    void stop();
    void processMessages();

private:
    std::atomic<bool> running;
    SocketType listener;
    std::vector<SocketType> clients;
    std::mutex clientsMutex;
    MessageHandler messageHandler;
    void removeClient(SocketType client);
    void handleClient(SocketType client);
    void sendToClient(const std::string& message, SocketType client);
    void broadcast(const std::string& message, SocketType clientSender);
};

#endif