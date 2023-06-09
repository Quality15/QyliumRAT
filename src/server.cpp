// server.cpp
// this code will listen on port and wait for targets connection

#include "server.h"

struct ThreadArgs {
    short port;
    PSTR ip;
};

void Server::listen_on_port(LPVOID lpParam)
{
    // args
    ThreadArgs* args = (ThreadArgs*)lpParam;
    short port = args->port;
    PSTR ip = args->ip;

    DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0) {
        printf("Failed to startup WSA\n");
        exit(1);
    }

    int sizeAddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    sListen = socket(AF_INET, SOCK_STREAM, 0);
    printf("Waiting for new connection on %s with port %i...\n", ip, port);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeAddr);

    if (newConnection == 0) {
        printf("Failed to connect\n");
    } else {
        char *clientIp = inet_ntoa(addr.sin_addr);
        printf("Successfully connected from %s!\n", clientIp);
    }

    delete args; // clear memory
}

void Server::start_thread(short port_arg, PSTR ip_arg)
{
    // args
    ThreadArgs* args = new ThreadArgs;
    args->port = port_arg;
    args->ip = ip_arg;
    
    DWORD ThreadID;
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&listen_on_port, (LPVOID)args, 0, &ThreadID);
    printf("%i\n%s\n", port_arg, ip_arg);
}

void Server::get_target_name() {
    Sleep(100);
    char computer_name[BUFF_SIZE];
    recv(newConnection, computer_name, BUFF_SIZE, 0);
    printf("Target's computer name: %s\n", computer_name);
}

int Server::close_connecion() {
    int iResult = shutdown(newConnection, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(newConnection);
        WSACleanup();
        return 1;
    }
}