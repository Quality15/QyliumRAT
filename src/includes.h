#define OEMRESOURCE

#ifdef _WIN32
#include <WinSock2.h>
#endif
#include <winsock.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "ws2_32")