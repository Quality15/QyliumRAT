// server.h

#pragma once
#include <WinSock2.h>
#include <winsock.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

#define BUFF_SIZE   1000

class Server
{
public:
    SOCKET newConnection;
    SOCKET sListen;
    SOCKADDR_IN addr;
    WSADATA wsaData;
    WORD DllVersion;

    void listen_on_port(short port, char *ip);
    char* recv_data();
    char* send_data();
    int close_connecion();
    void get_target_name();
};