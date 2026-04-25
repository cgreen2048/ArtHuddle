// server.cpp
#include <iostream>
#include <cstring>
#include <memory>


#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>

    using SocketType = SOCKET;
    #define CLOSE_SOCKET closesocket
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>

    using SocketType = int;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define CLOSE_SOCKET close
#endif

#define PORT 40666
#define BUFFER_SIZE 512

int main() {
#ifdef _WIN32
    WSADATA wsaData;

    // Step 1: Initialize WinSock on Windows
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }
#endif

    // Step 2: Create socket
    SocketType listener = socket(AF_INET, SOCK_STREAM, 0);

    if (listener == INVALID_SOCKET) {
        std::cout << "Socket creation failed\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    // Optional: allow port reuse after restarting server
    int opt = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Step 3: Bind to port
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listener, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << "Bind failed\n";
        CLOSE_SOCKET(listener);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    // Step 4: Listen
    if (listen(listener, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Listen failed\n";
        CLOSE_SOCKET(listener);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    while (true) {
        // Step 5: Accept client
        SocketType client = accept(listener, nullptr, nullptr);

        if (client == INVALID_SOCKET) {
            std::cout << "Accept failed\n";
            CLOSE_SOCKET(listener);
            #ifdef _WIN32
                    WSACleanup();
            #endif
                    return 1;
        }

        std::cout << "Client connected!\n";

        // Step 6: Receive messages
        char buffer[BUFFER_SIZE + 1];

        while (true) {
            int bytes = recv(client, buffer, BUFFER_SIZE, 0);

            if (bytes <= 0) {
                std::cout << "Client disconnected. Listening for new connections...\n";
                break;
            }

            buffer[bytes] = '\0';
            std::cout << "Received: " << buffer << "\n";
        }

        // Cleanup
        CLOSE_SOCKET(client);
    }

    
    CLOSE_SOCKET(listener);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}