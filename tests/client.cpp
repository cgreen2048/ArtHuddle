// client.cpp (Linux / WSL version)
#include "../API.hpp"
#include "../Global.hpp"
#include <memory>
#include "../Layout.hpp"
#include "../Button.hpp"
#include "../EventSystem.hpp"
#include "../Freehand.hpp"
#include "../MouseDownEvent.hpp"
#include "../MouseMotionEvent.hpp"
#include "../MouseUpEvent.hpp"


#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif


#include <unistd.h>
#include <iostream>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(40666);

    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (sockaddr*)&server, sizeof(server));

    std::cout << "Connected!\n";

    std::string msg;

    while (true) {
        std::getline(std::cin, msg);
        send(sock, msg.c_str(), msg.size(), 0);
    }

    close(sock);
}