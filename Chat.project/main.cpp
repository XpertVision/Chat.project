#include "Header.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;
HWND hLogWnd;
HWND hTxt;
HWND hLogin;
HWND hPass;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hRTFLib;
	hRTFLib = LoadLibrary(L"RICHED32.DLL");

	if (!hRTFLib)
	{
		MessageBox(NULL, L"RICHED32.DLL don't load", L"Error", MB_OK);
		return 1;
	}

	MSG mMessage;
	HWND hMainWnd;

	TCHAR mainWndClassName[] = L"Chat.project";

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASSEX wMainClass;
	ZeroMemory(&wMainClass, sizeof(wMainClass));

	wMainClass.cbSize        = sizeof(wMainClass);
	wMainClass.hInstance     = hInst;
	wMainClass.lpfnWndProc   = MainWndProc;
	wMainClass.lpszClassName = mainWndClassName;
	wMainClass.cbClsExtra    = NULL;
	wMainClass.cbWndExtra    = NULL;
	wMainClass.hbrBackground = CreateSolidBrush(RGB(4, 37, 65));
	wMainClass.style         = CS_VREDRAW | CS_HREDRAW;
	wMainClass.hIcon         = LoadIcon(hInst, MAKEINTRESOURCE(ID_MAIN_ICO));
	wMainClass.hIconSm       = LoadIcon(hInst, MAKEINTRESOURCE(ID_SMALL_ICO));

	if (!RegisterClassEx(&wMainClass))
	{
		MessageBox(NULL, L"Window class don't register", L"Error", MB_OK);
		return 1;
	}

	hMainWnd = CreateWindowEx(NULL, mainWndClassName, L"Chat.project", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, hInst, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, L"Window don't create", L"Error", MB_OK);
		return 1;
	}

	hLogWnd = CreateWindow(L"BUTTON", L"LogOn", WS_CHILD | WS_VISIBLE, 292, 370, 56, 25, hMainWnd, NULL, hInst, NULL);
	hLogin = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE | FW_HEAVY, 220, 190, 200, 20, hMainWnd, NULL, hInst, NULL);
	hPass = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE | FW_HEAVY | ES_PASSWORD, 220, 270, 200, 20, hMainWnd, NULL, hInst, NULL);

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
	HDC hdcMain;
	PAINTSTRUCT pstMain;
	RECT rMain;

	HFONT hfSegoe = CreateFont(0, 0, FW_DONTCARE, FW_DONTCARE, 200, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_STROKE_PRECIS, CLEARTYPE_QUALITY, FIXED_PITCH, L"Segoe UI");

	LPMINMAXINFO pInfo = NULL;
	POINT StartWndSize;

	switch (uMsg)
	{
	case WM_PAINT:
	{
		hdcMain = BeginPaint(hWnd, &pstMain);

		Gdiplus::Graphics gdiGrLogo(hdcMain);
		Gdiplus::Image *gdiImgLogo = new Gdiplus::Image(L"Logo.png");

		GetClientRect(hWnd, &rMain);

		SetTextColor(hdcMain, RGB(200, 200, 200));
		SetBkColor(hdcMain, RGB(4, 37, 65));

		SelectObject(hdcMain, hfSegoe);

		TextOut(hdcMain, 145, 270, L"Password", 8);
		TextOut(hdcMain, 173, 190, L"Login", 5);

		gdiGrLogo.DrawImage(gdiImgLogo, 256, 40, 128, 128);

		EndPaint(hWnd, &pstMain);
	}
		break;
	case WM_COMMAND:
	//	switch (wParam)
	//	{

//		}
		break;
	case WM_GETMINMAXINFO:
	{
		pInfo = (LPMINMAXINFO)lParam;
		StartWndSize = { 640, 480 };
		pInfo->ptMinTrackSize = StartWndSize;
		pInfo->ptMaxTrackSize = StartWndSize;
		return 0;
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return NULL;
}