#include "Header.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoginEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoginPassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LogonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInstCopy;
HWND hLogButton;
HWND hTxt;
HWND hLogin;
HWND hPass;
WNDPROC wpLogin;
WNDPROC wpPass;
WNDPROC wpLogon;

HWND hMainWnd;

int nCmdShowCopy;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hRTFLib;
	hRTFLib = LoadLibrary(L"RICHED32.DLL");

	if (!hRTFLib)
	{
		MessageBox(NULL, L"RICHED32.DLL don't load", L"Error", MB_OK);
		return 1;
	}

	MSG mMessage;

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
	wMainClass.hCursor       = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&wMainClass))
	{
		MessageBox(NULL, L"Window class don't register", L"Error", MB_OK);
		return 1;
	}

	hInstCopy = hInst;
	nCmdShowCopy = nCmdShow;

	hMainWnd = CreateWindowEx(NULL, mainWndClassName, L"Chat.project", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480, NULL, NULL, hInst, NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, L"Window don't create", L"Error", MB_OK);
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
	HDC hdcMain;
	PAINTSTRUCT pstMain;

	LPDRAWITEMSTRUCT lpdrawstLogon = NULL;

	HFONT hfSegoe = CreateFont(22, 0, 0, 0, 200, 0, 0, 0, OEM_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS
		, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, L"Segoe UI");

	LPMINMAXINFO pInfo = NULL;
	POINT StartWndSize;

	static Gdiplus::Graphics* gdiImg = NULL;

	static int iWindowType(LOGIN_WINDOW);

	switch (uMsg)
	{
	case WM_CREATE:
	{
		if (iWindowType == LOGIN_WINDOW)
		{
			InitHandles(hWnd);

			hdcMain = GetDC(0);
			int x, y;
			x = GetDeviceCaps(hdcMain, HORZRES);
			y = GetDeviceCaps(hdcMain, VERTRES);

			SetWindowPos(hWnd, NULL, ((x - 640) / 2), ((y - 480) / 2), 0, 0, SWP_NOSIZE);

			ReleaseDC(0, hdcMain);

			InvalidateRect(hWnd, NULL, TRUE);
			SetWindowPos(hWnd, HWND_TOP, 0, 0, 640, 480, SWP_NOMOVE);
		}
		else if (iWindowType == CHAT_WINDOW)
		{
			hdcMain = GetDC(0);
			int x, y;
			x = GetDeviceCaps(hdcMain, HORZRES);
			y = GetDeviceCaps(hdcMain, VERTRES);

			SetWindowPos(hWnd, NULL, ((x - 800) / 2), ((y - 600) / 2), 0, 0, SWP_NOSIZE);

			ReleaseDC(0, hdcMain);

			//CloseWindow(hLogin); VERY FUNY RESULT! ^^
			//HWND hTypeMessage = CreateWindow(L"RICHEDIT", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | WS_BORDER, 200, 480, 585, 121, hWnd, (HMENU)12345, hInstCopy, NULL);
			//HWND hMainChat = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER, 0, 0, 200, 601, hWnd, (HMENU)141231, hInstCopy, NULL);

			SetWindowPos(hWnd, HWND_TOP, 0, 0, 800, 600, SWP_NOMOVE);
		}
		else if (iWindowType == CONNECTING_WINDOW)
		{
			hdcMain = GetDC(0);
			int x, y;
			x = GetDeviceCaps(hdcMain, HORZRES);
			y = GetDeviceCaps(hdcMain, VERTRES);

			SetWindowPos(hWnd, NULL, ((x - 640) / 2), ((y - 480) / 2), 0, 0, SWP_NOSIZE);

			ReleaseDC(0, hdcMain);

			DestroyWindow(hLogin);
			DestroyWindow(hPass);
			DestroyWindow(hLogButton);

			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	break;
	case WM_PAINT:
	{
		if (iWindowType == LOGIN_WINDOW)
		{
			hdcMain = BeginPaint(hWnd, &pstMain);

			SetTextColor(hdcMain, RGB(200, 200, 200));
			SetBkColor(hdcMain, RGB(4, 37, 65));

			SelectObject(hdcMain, hfSegoe);

			SetTextAlign(hdcMain, TA_RIGHT);
			TextOutW(hdcMain, 210, 270, L"Password", 8);
			TextOutW(hdcMain, 210, 190, L"Login", 5);
			SetTextAlign(hdcMain, TA_LEFT);

			gdiImg = new Gdiplus::Graphics(hdcMain);

			gdiImg->DrawImage(SimpleImgLoad.GetImg(ID_LOGO, hInstCopy), 256, 40, 128, 128);
			SimpleImgLoad.Release();

			delete gdiImg;

			EndPaint(hWnd, &pstMain);
		}
		else if (iWindowType == CHAT_WINDOW)
		{
			hdcMain = BeginPaint(hWnd, &pstMain);

			SetBkColor(hdcMain, RGB(4, 37, 65));

			EndPaint(hWnd, &pstMain);
		}
		else if (iWindowType == CONNECTING_WINDOW)
		{
			hdcMain = BeginPaint(hWnd, &pstMain);

			SetBkColor(hdcMain, RGB(4, 37, 65));

			EndPaint(hWnd, &pstMain);
		}
	}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_LOGON && HIWORD(wParam) == BN_CLICKED)
		{
			iWindowType = CONNECTING_WINDOW;
			SetTimer(hWnd, ID_LOG_ANIM_TIMER, 50, NULL);
			SendMessage(hWnd, WM_CREATE, wParam, lParam);
		}
	}
	break;
	case WM_KEYUP: //FOR DEBUG
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			if (iWindowType == CHAT_WINDOW)
			{
				iWindowType = LOGIN_WINDOW;
				SendMessage(hWnd, WM_CREATE, wParam, lParam);
			}
		}
		break;
		}
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case ID_LOG_ANIM_TIMER:
		{
			static int iKillStep = 0;
			static int iImg = ID_LOGIN_ANIM_START;
			hdcMain = GetDC(hWnd);

			gdiImg = new Gdiplus::Graphics(hdcMain);
			gdiImg->DrawImage(SimpleImgLoad.GetImg(iImg, hInstCopy), 160, 150, 320, 180);
			SimpleImgLoad.Release();

			delete gdiImg;
			ReleaseDC(hWnd, hdcMain);

			iKillStep++;
			if (iKillStep == 8)
			{
				iWindowType = CHAT_WINDOW;
				iKillStep = 0;
				KillTimer(hWnd, ID_LOG_ANIM_TIMER);
				SendMessage(hWnd, WM_CREATE, wParam, lParam);
			}

			if (iImg < ID_LOGIN_ANIM_LAST)
			{
				iImg++;
			}
			else
			{
				iImg = ID_LOGIN_ANIM_START;
			}
		}
		break;
		}
	}
	break;
	case WM_DRAWITEM:
	{
		if (iWindowType == LOGIN_WINDOW)
		{
			lpdrawstLogon = (LPDRAWITEMSTRUCT)lParam;

			if (lpdrawstLogon->hwndItem == hLogButton)
			{
				FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));

				gdiImg = new Gdiplus::Graphics(lpdrawstLogon->hDC);
				gdiImg->DrawImage(SimpleImgLoad.GetImg(ID_LOGON_DEF, hInstCopy), 0, 0, 48, 48);
				SimpleImgLoad.Release();

				switch (lpdrawstLogon->CtlID)
				{
				case ID_LOGON:
				{
					if (lpdrawstLogon->itemState & ODS_FOCUS)
					{
						FillRect(lpdrawstLogon->hDC, &lpdrawstLogon->rcItem, CreateSolidBrush(RGB(4, 37, 65)));

						gdiImg->DrawImage(SimpleImgLoad.GetImg(ID_LOGON_SET, hInstCopy), 0, 0, 48, 48);
						SimpleImgLoad.Release();
					}
				}

				delete gdiImg;

				break;
				}
			}
		}
	}
	break;
	case WM_SETCURSOR:
	{
		static HWND hFocused(NULL);
		if (hLogButton == (HWND)wParam)
		{
			if (GetFocus() != hLogButton)
			{
				hFocused = GetFocus();
				SetFocus(hLogButton);
			}
		}
		else
		{
			if (GetFocus() == hLogButton)
			{
				SetFocus(hFocused);
			}
		}
		DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	break;
	case WM_GETMINMAXINFO:
	{
		if (iWindowType == LOGIN_WINDOW || iWindowType == CONNECTING_WINDOW)
		{
			pInfo = (LPMINMAXINFO)lParam;
			StartWndSize = { 640, 480 };
			pInfo->ptMinTrackSize = StartWndSize;
			pInfo->ptMaxTrackSize = StartWndSize;
		}
		else if (iWindowType == CHAT_WINDOW)
		{
			pInfo = (LPMINMAXINFO)lParam;
			StartWndSize = { 800, 640 };
			pInfo->ptMinTrackSize = StartWndSize;
		}
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

LRESULT CALLBACK LoginEditProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
	{
		if (wParam == VK_TAB)
		{
			SetFocus(hPass);
		}
		else if (search(wchAccesChar, wParam, sizeof(wchAccesChar)))
		{
			return CallWindowProc(wpLogin, hWnd, uMsg, wParam, lParam);
		}
	}
	break;
	default:
		return CallWindowProc(wpLogin, hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK LoginPassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CHAR:
	{
		if (wParam == VK_TAB)
		{
			SetFocus(hLogButton);
			break;
		}
		else if (search(wchAccesChar, wParam, sizeof(wchAccesChar)))
		{
			return CallWindowProc(wpPass, hWnd, uMsg, wParam, lParam);
		}
	}
	break;
	default:
		return CallWindowProc(wpPass, hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK LogonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	if (wParam == VK_TAB)
		{
			SetFocus(hLogin);
		}
		else if (wParam == VK_RETURN)
		{
			SendNotifyMessage(hMainWnd, WM_COMMAND, ID_LOGON | BN_CLICKED, NULL);
		}
	break;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_LOGON)
		{
			MessageBox(NULL, L"YES\n!", L"OK", MB_OK);
		}
	}
	break;
	default:
		return CallWindowProc(wpLogon, hLogButton, uMsg, wParam, lParam);
	}
	return 0;
}