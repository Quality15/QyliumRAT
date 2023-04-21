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

struct ThreadAgrs;
class Server
{
public:
    SOCKET newConnection;
    SOCKET sListen;
    SOCKADDR_IN addr;
    WSADATA wsaData;
    WORD DllVersion;

    void listen_on_port(LPVOID lpParam);
    void start_thread(short port_arg, PSTR ip_arg);
    
    char* recv_data();
    char* send_data();
    
    int close_connecion();
    
    void get_target_name();
};