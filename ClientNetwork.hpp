#ifndef __CLIENT_NETWORK_HPP__
#define __CLIENT_NETWORK_HPP__


#include <string>
#include <iostream>
#include <memory>
#include <cstring>


// client.cpp (Linux / WSL version)
#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif


bool connectToServer(const char* host, int port);
void sendToServer(const std::string& message);
void receiveMessagesLoop();
void closeConnection();


#endif