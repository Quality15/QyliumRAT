// server.cpp
// NOGUI
// this code will listen on port and wait for targets connection

#include "includes.h"

int main() 
{
    WSADATA wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0) {
        printf("Failed to startup WSA\n");
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeAddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(4444);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
    printf("Waiting for new connection...\n");
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeAddr);

    if (newConnection == 0) {
        printf("Failed to connect\n");
    } else {
        printf("Successfully connected!\n");
    }

    system("PAUSE");
    return 0;
}