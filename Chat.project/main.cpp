#include "Header.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK LogWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR lpCmdLine, int nCmdShow)
{
	/*HINSTANCE hRTFLib;
	hRTFLib = */LoadLibrary(L"RICHED32.DLL");

	MSG mMessage;
	HWND hMainWnd;
	HWND hLogWnd;
	TCHAR mainWndClassName[] = L"Chat.project";

	WNDCLASSEX wMainClass;
	ZeroMemory(&wMainClass, sizeof(wMainClass));

	wMainClass.cbSize        = sizeof(wMainClass);
	wMainClass.hInstance     = hInst;
	wMainClass.lpfnWndProc   = MainWndProc;
	wMainClass.lpszClassName = mainWndClassName;
	wMainClass.cbClsExtra    = NULL;
	wMainClass.cbWndExtra    = NULL;
	wMainClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wMainClass.style         = CS_VREDRAW | CS_HREDRAW;
	wMainClass.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(ID_MAIN_ICO));

	if (!RegisterClassEx(&wMainClass))
	{
		MessageBox(NULL, L"Window class don'r register", L"Error", MB_OK);
		return 1;
	}

	hMainWnd = CreateWindowEx(NULL, mainWndClassName, L"Chat.project", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, hInst, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, L"Window don't create", L"Error", MB_OK);
		return 1;
	}

	hLogWnd = CreateDialog(hInst, MAKEINTRESOURCE(ID_LOG_WINDOW), hMainWnd, (DLGPROC)LogWndProc);
	if (!hLogWnd)
	{
		MessageBox(NULL, L"Sorry", L"Error", MB_OK);
		return 1;
	}

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&mMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&mMessage);
		DispatchMessage(&mMessage);
	}

	return mMessage.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO pInfo = NULL;
	POINT StartWndSize;

	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{

		}
		break;
	case WM_GETMINMAXINFO:
		pInfo = (LPMINMAXINFO)lParam;
		StartWndSize = { 640, 480 };
		pInfo->ptMinTrackSize = StartWndSize;
		pInfo->ptMaxTrackSize = StartWndSize;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return NULL;
}

BOOL CALLBACK LogWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_LOGIN: break;
		case ID_PASS: break;
		}
		break;
	}

	return FALSE;
}