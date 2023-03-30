// server.cpp
// NOGUI
// this code will listen on port and wait for targets connection

#include "server.h"

void Server::listen_on_port(short port, char *ip)
{
    WSADATA wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0) {
        printf("Failed to startup WSA\n");
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeAddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    printf("Waiting for new connection on %s with port %i...\n", ip, port);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeAddr);

    if (newConnection == 0) {
        printf("Failed to connect\n");
    } else {
        printf("Successfully connected!\n");
    }
}