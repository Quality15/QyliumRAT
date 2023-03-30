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

class Server
{
public:
    void listen_on_port(short port, char *ip);
    void close_connecion();
};