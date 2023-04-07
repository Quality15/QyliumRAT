// client.h

#pragma once
#include <WinSock2.h>
#include <winsock.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

bool isAdmin();
class Client 
{
public:
    WSADATA wsaData;
    WORD DllVersion;
    SOCKET wSock;
    SOCKET connection;
    SOCKADDR_IN addr;
    STARTUPINFO sui;
    PROCESS_INFORMATION pi;

    int connect_to(short port, char *ip);
    void get_computer_name(SOCKET socket);
};