#ifndef RELAY_SERVER_HPP
#define RELAY_SERVER_HPP

#include <atomic>

#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    using SocketType = SOCKET;
#else
    using SocketType = int;
#endif

class RelayServer {
public:
    RelayServer();

    void start();
    void stop();

private:
    std::atomic<bool> running;
    SocketType listener;
};

#endif