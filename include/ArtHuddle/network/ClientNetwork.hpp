#ifndef __CLIENT_NETWORK_HPP__
#define __CLIENT_NETWORK_HPP__


#include <string>
#include <iostream>
#include <memory>
#include <cstring>
#include <functional>
#include "ArtHuddle/elements/Layout.hpp"
#include "ArtHuddle/network/MessageHandler.hpp"


// client.cpp (Linux / WSL version)
#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

class ClientNetwork {
    private:
        int socketIdentifier = 0;
        bool connected = false;
        std::function<void()> onDisconnect;
        MessageHandler messageHandler;
    public:
        ClientNetwork(Layout* layout);
        bool connectToServer(const char* host, int port);
        void sendToServer(const std::string& message);
        void receiveMessages();
        void processMessages();
        void closeConnection();
        int getSocketIdentifier();
        bool isConnected();
        void setDisconnectCallback(std::function<void()> callback);

};

#endif