#define OEMRESOURCE

#include <WinSock2.h>
#include <winsock.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <wingdi.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <tchar.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "ws2_32")

#define OnMenuExitClicked       1
#define OnMenuAboutClicked      2
#define OnMenuBuildClicked      3
#define OnButtonListenClicked   4

#define IPStaticWidth           20

#define PortStaticWidth         35
#define PortStaticHeight        15
#define PortIndex               200
#define IPIndex                 300

void MainWndMenus(HWND hWnd);
void MainWndWidgets(HWND hWnd);

bool isListening;
short port;
TCHAR ip[1024];

HWND PortWnd;
HWND IpWnd;
HWND ListenBtn;
HWND StatusLabel;

void start_listen(HWND hWnd, HWND portWnd, HWND ipWnd);
