// deschid o fila noua
// si de care am nevoie
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateMenubar(HWND);
void OpenDialog(HWND);
void LoadFile(LPSTR);

#define IDM_FILE_NEW 1
HWND ghwndEdit;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASS wc = { 0 };
	wc.lpszClassName = TEXT("Opendialog");
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);


	RegisterClass(&wc);
	CreateWindow(wc.lpszClassName, TEXT("Opendialog"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		150, 150, 265, 200, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_CREATE:
		ghwndEdit = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, TEXT("edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE,
			0, 0, 260, 180,
			hwnd, (HMENU)1, NULL, NULL);


		CreateMenubar(hwnd);
		break;

	case WM_SIZE:
		SetWindowPos(ghwndEdit, NULL, 0, 0, LOWORD(lParam), HIWORD(lParam),
			SWP_NOMOVE | SWP_NOZORDER);
		break;

	case WM_COMMAND:
		if (wParam == IDM_FILE_NEW) {
			OpenDialog(hwnd);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CreateMenubar(HWND hwnd) {

	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();
	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, TEXT("&File"));
	AppendMenu(hMenu, MF_STRING, IDM_FILE_NEW, TEXT("&Open"));
	SetMenu(hwnd, hMenubar);
}

void OpenDialog(HWND hwnd) {

	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All files(*.*)\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
		LoadFile(ofn.lpstrFile);
}

void LoadFile(LPSTR file) {

	HANDLE hFile;
	DWORD dwSize;
	DWORD dw;

	LPBYTE lpBuffer = NULL;

	hFile = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	dwSize = GetFileSize(hFile, NULL);
	lpBuffer = (LPBYTE)HeapAlloc(GetProcessHeap(),
		HEAP_GENERATE_EXCEPTIONS, dwSize + 1);
	ReadFile(hFile, (LPWSTR)lpBuffer, dwSize, &dw, NULL);
	CloseHandle(hFile);
	lpBuffer[dwSize] = 0;
	SetWindowText(ghwndEdit, (LPSTR)lpBuffer);
	HeapFree(GetProcessHeap(), 0, lpBuffer);
}






// ce era bun
//era mai bine asa
/*
#include <windows.h>
#include<mmsystem.h>
#include "resource.h"
#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier
HWND hEdit;
const char g_szClassName[] = "myWindowClass";
//bool PLaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);
// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Create an edit box
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
			"EDIT",
			"",
			WS_CHILD | WS_VISIBLE |
			ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
			50,
			100,
			200,
			100,
			hwnd,
			(HMENU)IDC_MAIN_EDIT,
			GetModuleHandle(NULL),
			NULL);
		HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hEdit,
			WM_SETFONT,
			(WPARAM)hfDefault,
			MAKELPARAM(FALSE, 0));
		SendMessage(hEdit,
			WM_SETTEXT,
			NULL,
			(LPARAM)"Insert text here...");
		HWND hWndButton = CreateWindowEx(NULL,
			"BUTTON",
			"OK",
			WS_TABSTOP | WS_VISIBLE |
			WS_CHILD | BS_DEFPUSHBUTTON,
			50,
			220,
			100,
			24,
			hwnd,
			(HMENU)IDC_MAIN_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		SendMessage(hWndButton,
			WM_SETFONT,
			(WPARAM)hfDefault,
			MAKELPARAM(FALSE, 0));
	}break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_MAIN_BUTTON:
		{
			char buffer[256];
			SendMessage(hEdit,
				WM_GETTEXT,
				sizeof(buffer) / sizeof(buffer[0]),
				reinterpret_cast<LPARAM>(buffer));
			MessageBox(NULL,
				buffer,
				"Information (Ce ai introdus de la tastatura)",
				MB_ICONINFORMATION);
		}
		break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}


LPCTSTR Caption = "Interfata de Programare a Aplicatiei";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	//PlaySound("D:\\Laboratoare info\\Semestrul 2\\Laboratoare scoala\\Win32-trial\\Win32-trial\\Imn.wav", NULL, SND_SYNC | SND_NODEFAULT);
	MessageBox(NULL, "Bine ati venit la proiectul de compresie a datelor ! \n", "Start", NULL);
	MessageBox(NULL,
		"Welcome to Win32 Application Development\n"
		"You will may compress different data types and "
		"in this WAY you will efficiently use the memory : yes, yes, yes... trust on me :) \n"
		"Are you ready to rumble !!!!!!!!!!!!!!",
		Caption,MB_YESNOCANCEL | MB_ICONQUESTION);

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInstance,MAKEINTRESOURCEA(IDC_TARGET));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"Compresie",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


*/







// alt ceva
/*#include <windows.h>
#include "resource.h"
const char g_szClassName[] = "myWindowClass";
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		char szFileName[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(NULL);
		GetModuleFileName(hInstance, szFileName, MAX_PATH);
		MessageBox(hwnd, szFileName, "This program is:", MB_OK |
			MB_ICONINFORMATION);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		//PostMessage(hwnd, WM_CLOSE, 0, 0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCEA(IDC_TARGET));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}*/

